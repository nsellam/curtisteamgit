/**
 * @file    rear_motors.c
 * @author  Curtis Team
 * @brief   Functions to handle rear motors
 */
 
 /* Includes ------------------------------------------------------------------*/
#include "rear_motors.h"
#include "stm32f10x_conf.h"
#include <math.h>
#include "motors.h"
#include "speed_sensors.h"
#include "hall_sensors.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
int16_t current = 0; 
volatile static int16_t car_speed = 0;
volatile int16_t speed_cmd;
volatile static float duty_cycle_L = MOTORS_PWM_ZERO;
uint32_t RearMotors_remainingTimeInCommandPeriod = MOTORS_COMMAND_TIME_BETWEEN_TWO_UPDATES;
static float out_prec = 0;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



int16_t car_model (float in) {
    
    float K_model = 250.0;   // speed in cm/s
    float T_model = 0.1;
    int16_t out;
    out = (K_model * (float)(in-MOTORS_PWM_ZERO) - T_model * out_prec);
    out_prec = (float)out;
    return out;
}




void RearMotors_Callback(void) {
    RearMotors_remainingTimeInCommandPeriod --;
    
    if (RearMotors_remainingTimeInCommandPeriod == 0) {
        rear_motor_L_control(speed_cmd);
        RearMotors_remainingTimeInCommandPeriod = MOTORS_COMMAND_TIME_BETWEEN_TWO_UPDATES;
    }
}


/**
 * @brief		Computes the next iteration Motor Duty-Cycle command
 * @param		speed_cmd the speed input command for the control loop (cm/s)
 * @param		current the current in the motor (mA)
 * @param		speed the car speed (cm/s)
 * @return	the duty-cycle command for the motor
*/

float ComputeMotorCommand (int16_t speed_cmd, int16_t current, int16_t speed){
    
    float dc;         //out duty cycle;
    volatile int32_t in_PI;
    float current_f = (float)current;
    volatile float coef_in_PI;   // to adjust PI input depending on how close from MAX_CURRENT we are
   
    // see Simulink model to understand
    
    // duty cycle is 50 if current reaches MAX_CURRENT
	if (fabs (current_f > MAX_CURRENT)) { 
        dc = (uint8_t)MOTORS_PWM_ZERO;
    }   

    // If MAX_CURRENT is not reached     
	else {
        // PI controller input depends on how close from MAX_CURRENT is the current
        coef_in_PI = (MAX_CURRENT - fabs(current_f)) / MAX_CURRENT;

        in_PI = (int32_t)((int16_t)((float)((int32_t)(speed_cmd - speed)) * coef_in_PI));
        
        
        
        dc = PI_Controller(in_PI) ; 
        
    }        
    
    // compute the motor command (duty cycle)
    return dc;
}


/**
 * @brief		Applies a PI controller to the input
 * @param		in PI controller input
 * @return	PI controller output
*/

float PI_Controller (int32_t in)
{
	
	// PI controller
static const float Kp = 0.000005;
static const float Ki = 0.0;
static const float T = 0.001;                  // 1Khz control loop frequency
//volatile static const float a1_PI = Kp + T*Ki/2.0 ;      // coef. formula PI controller
//volatile static const float a2_PI = Kp - T*Ki/2.0 ; 
   volatile static const float a1_PI =  T*Ki/2.0 - Kp ;      // coef. formula PI controller
   volatile static const float a2_PI =  T*Ki/2.0 + Kp; 

static float outPI_prec_no_offset = 0.0, unsat_PI_output_f = MOTORS_PWM_ZERO;            // buffer previous in & out

	float in_f; 
	float PI_output_f;
    float K_AW = 0.6;
    float AW_f = 0.0;
   
        
    
    in_f = (float)(in);        
	
    // Simple Anti-windup
    if (unsat_PI_output_f > MOTORS_PWM_MAX)
       AW_f =  K_AW*(unsat_PI_output_f  - MOTORS_PWM_MAX); 
    else if (unsat_PI_output_f  < MOTORS_PWM_MIN)
       AW_f = K_AW*(unsat_PI_output_f  - MOTORS_PWM_MIN);
    else 
       AW_f = 0.0;        
    
	// Compute PI output - do not forget the 50% offset
    unsat_PI_output_f = outPI_prec_no_offset + Kp*in_f - AW_f;
    unsat_PI_output_f += MOTORS_PWM_ZERO;
	
	// Saturate PI output between Min and Max duty-cycles
	if (unsat_PI_output_f > MOTORS_PWM_MAX)
		PI_output_f = MOTORS_PWM_MAX;
	else if (unsat_PI_output_f < MOTORS_PWM_MIN)
		PI_output_f = MOTORS_PWM_MIN;
    else
        PI_output_f = unsat_PI_output_f;
	
		
	// Update variables for next iteration
  outPI_prec_no_offset = PI_output_f - MOTORS_PWM_ZERO;
  return PI_output_f;
}




/**
 * @brief		The core of the control loop for rear motor left
 * @param		the speed command 
 * @return	void
*/

 

void rear_motor_L_control (int16_t speed_cmd){

    float motor_speed_L;
    
    // Command must be send without jitter...
    motor_speed_L = (duty_cycle_L - MOTORS_PWM_ZERO) / ((MOTORS_PWM_DELTA_MAX)/(MOTORS_SPEED_DELTA));
    Motor_setSpeed(REAR_MOTOR_L, motor_speed_L);

    // ... so we need to compute the command for next send.
    car_speed = SpeedSensor_get(SPEED_CM_S, SPEED_SENSOR_L);     
    duty_cycle_L = ComputeMotorCommand(speed_cmd, current, car_speed);

}


