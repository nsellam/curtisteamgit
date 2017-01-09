/**
 * @file    rear_motors.c
 * @author  Curtis Team
 * @brief   Functions to handle rear motors 
 */
 
/* Includes ------------------------------------------------------------------*/
#include "rear_motors.h"

#include "stm32f10x_conf.h"
#include "motors.h"
#include "speed_sensors.h"
#include "hall_sensors.h"
#include "it_handlers.h"
#include "modules_definitions.h"

#include <math.h>


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/

/**
 * @brief   Number of systick iteruptions to wait until next motors command refresh period
*/
uint32_t RearMotors_remainingTimeInCommandPeriod = MOTORS_COMMAND_TIME_BETWEEN_TWO_UPDATES; 

/**
 * @brief memorizes the input command for the motors control loop  -  same for left and right motors
 */
    volatile int16_t speed_cmd;

/* Private variables ---------------------------------------------------------*/

/**
 * @brief memorizes the current int the motors we measure
 */
    int16_t current = 0; 
    
/**
 * @brief memorizes the measured left wheel speed  
 */    
    volatile static int16_t wheel_speed_L = 0;
    
/**
 * @brief memorizes the measured right wheel speed  
 */    
    volatile static int16_t wheel_speed_R = 0;
    
/**
 * @brief memorizes the duty-cycle for left wheel
 */  
    volatile static float duty_cycle_L = MOTORS_PWM_ZERO;
    
/**
 * @brief memorizes the duty-cycle for right wheel
 */  
    volatile static float duty_cycle_R = MOTORS_PWM_ZERO;


/* Private function prototypes -----------------------------------------------*/


float ComputeMotorCommand_L (int16_t speed_cmd, int16_t current, int16_t speed);
float ComputeMotorCommand_R (int16_t speed_cmd, int16_t current, int16_t speed);
float PI_Controller_L (int32_t in);
float PI_Controller_R (int32_t in);
void  RearMotors_resetTimeToNextCommandPeriod();

/* Public functions ----------------------------------------------------------*/

void RearMotors_Callback(void) {
  RearMotors_remainingTimeInCommandPeriod --;
  if (RearMotors_remainingTimeInCommandPeriod == 0) {
    //CMD
    rear_motor_L_control (speed_cmd);
    rear_motor_R_control (speed_cmd);
    RearMotors_resetTimeToNextCommandPeriod();
  }
}


/**
 * @brief		The core of the control loop for rear motor left
 * @param		the speed command 
 * @return	void
*/

 void rear_motor_L_control (int16_t speed_cmd){

    // declarations
    float motor_speed_L;
    
    // core
    motor_speed_L = (duty_cycle_L - MOTORS_PWM_ZERO) / ((MOTORS_PWM_DELTA_MAX)/(MOTORS_SPEED_DELTA));
    Motor_setSpeed(REAR_MOTOR_L, motor_speed_L);

    duty_cycle_L = ComputeMotorCommand_L (speed_cmd, current, wheel_speed_L);       
}
 
/**
 * @brief		The core of the control loop for rear motor left
 * @param		the speed command 
 * @return	void
*/

 void rear_motor_R_control (int16_t speed_cmd){

    // declarations
    float motor_speed_R;
    
    // core
    motor_speed_R = (duty_cycle_R - MOTORS_PWM_ZERO) / ((MOTORS_PWM_DELTA_MAX)/(MOTORS_SPEED_DELTA));
    Motor_setSpeed(REAR_MOTOR_R, motor_speed_R);

    duty_cycle_R = ComputeMotorCommand_R (speed_cmd, current, wheel_speed_R);       
}

/* Private functions ---------------------------------------------------------*/


/**
 * @brief		Computes the next iteration Motor Duty-Cycle command (left motor)
 * @param		speed_cmd the speed input command for the control loop (cm/s)
 * @param		current the current in the motor (mA)
 * @param		speed the car speed (cm/s)
 * @return	the duty-cycle command for the motor
*/

float ComputeMotorCommand_L (int16_t speed_cmd, int16_t current, int16_t speed){
    
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
        
        
        
        dc = PI_Controller_L(in_PI) ; 
        
    }        
    
    // compute the motor command (duty cycle)
    return dc;
}



/**
 * @brief		Computes the next iteration Motor Duty-Cycle command (right motor)
 * @param		speed_cmd the speed input command for the control loop (cm/s)
 * @param		current the current in the motor (mA)
 * @param		speed the car speed (cm/s)
 * @return	the duty-cycle command for the motor
*/

float ComputeMotorCommand_R (int16_t speed_cmd, int16_t current, int16_t speed){
    
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
        
        
        
        dc = PI_Controller_R(in_PI) ; 
        
    }        
    
    // compute the motor command (duty cycle)
    return dc;
}


/**
 * @brief		Applies a PI controller to the input (left motor)
 * @param		in PI controller input
 * @return	PI controller output
*/

float PI_Controller_L (int32_t in)
{
	
	// PI controller
static const float Kp = 0.000005;
static const float Ki = 0.0;
static const float T = 0.001;                  // 1Khz control loop frequency
//volatile static const float a1_PI = Kp + T*Ki/2.0 ;      // coef. formula PI controller
//volatile static const float a2_PI = Kp - T*Ki/2.0 ; 
   volatile static const float a1_PI =  T*Ki/2.0 - Kp ;      // coef. formula PI controller
   volatile static const float a2_PI =  T*Ki/2.0 + Kp; 

static float outPI_prec_L_no_offset = 0.0, unsat_PI_output_f = MOTORS_PWM_ZERO;            // buffer previous in & out

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
    unsat_PI_output_f = outPI_prec_L_no_offset + Kp*in_f - AW_f;
    unsat_PI_output_f += MOTORS_PWM_ZERO;
	
	// Saturate PI output between Min and Max duty-cycles
	if (unsat_PI_output_f > MOTORS_PWM_MAX)
		PI_output_f = MOTORS_PWM_MAX;
	else if (unsat_PI_output_f < MOTORS_PWM_MIN)
		PI_output_f = MOTORS_PWM_MIN;
    else
        PI_output_f = unsat_PI_output_f;
	
		
	// Update variables for next iteration
  outPI_prec_L_no_offset = PI_output_f - MOTORS_PWM_ZERO;
  return PI_output_f;
}



/**
 * @brief		Applies a PI controller to the input (right motor)
 * @param		in PI controller input
 * @return	PI controller output
*/

float PI_Controller_R (int32_t in)
{
	
	// PI controller
static const float Kp = 0.000005;
static const float Ki = 0.0;
static const float T = 0.001;                  // 1Khz control loop frequency
//volatile static const float a1_PI = Kp + T*Ki/2.0 ;      // coef. formula PI controller
//volatile static const float a2_PI = Kp - T*Ki/2.0 ; 
   volatile static const float a1_PI =  T*Ki/2.0 - Kp ;      // coef. formula PI controller
   volatile static const float a2_PI =  T*Ki/2.0 + Kp; 

static float outPI_prec_R_no_offset = 0.0, unsat_PI_output_f = MOTORS_PWM_ZERO;            // buffer previous in & out

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
    unsat_PI_output_f = outPI_prec_R_no_offset + Kp*in_f - AW_f;
    unsat_PI_output_f += MOTORS_PWM_ZERO;
	
	// Saturate PI output between Min and Max duty-cycles
	if (unsat_PI_output_f > MOTORS_PWM_MAX)
		PI_output_f = MOTORS_PWM_MAX;
	else if (unsat_PI_output_f < MOTORS_PWM_MIN)
		PI_output_f = MOTORS_PWM_MIN;
    else
        PI_output_f = unsat_PI_output_f;
	
		
	// Update variables for next iteration
  outPI_prec_R_no_offset = PI_output_f - MOTORS_PWM_ZERO;
  return PI_output_f;
}

/**
 * @brief       Reinit private variable indicating time remainng before the motor control period.
 * @retval      None
*/
void RearMotors_resetTimeToNextCommandPeriod(void) {
  RearMotors_remainingTimeInCommandPeriod = MOTORS_COMMAND_TIME_BETWEEN_TWO_UPDATES;
}
