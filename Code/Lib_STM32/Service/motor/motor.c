/**
 * @file motor.h
 * @author Curtis team
 * @brief Service library that allows to manipulate motors
 */

/********************************/
/*       LIBRARIES              */
/********************************/
#include "motor.h"

#include <timer.h>
#include <gpio2.h>
#include <pwm.h>


/********************************/
/*         CONSTANTS            */
/********************************/

/**
* @def TIMx
* @brief Timer used to motors PWM generation
*/
#define TIMx TIM1

/**
* @def CH
* @brief Channel used to motors PWM generation
*/
#define CH 1

/**
* @def Frequence_Hz
* @brief Frequency used to motors PWM generation in Hz
*/
#define Frequence_Hz (float)(20e3) //in Hz

/**
* @def GPIOx
* @brief GPIO used to enable the motors
*/
#define GPIOx GPIOC

/**
* @def ENABLE_PIN
* @brief Pin used to enable the motors
*/
#define ENABLE_PIN 6

/**
* @def PWM_MIN
* @brief Minimum PWM value used to turn the motors backwards to their maximum
*/
#define PWM_MIN ((float)0.245)

/**
* @def PWM_MAX
* @brief Maximum PWM value used to turn the motors forwards to their maximum
*/
#define PWM_MAX ((float)0.754)

/**
* @def PWM_ZERO
* @brief Zero PWM value used to turn the motors off
*/
#define PWM_ZERO ((float)0.500)

/**
* @def PWM_DELTA_MAX
* @brief Maximum variation of the PWM value from the PWM_ZERO value
*/
#define PWM_DELTA_MAX (((PWM_MAX - PWM_ZERO) < (PWM_ZERO - PWM_MIN)) ? (PWM_MAX - PWM_ZERO) : (PWM_ZERO - PWM_MIN))

/**
* @def SPEED_DELTA
* @brief Variation of the speed value between its maximum or minimum value and the zero
*/
#define SPEED_DELTA ((float)1.0)

/**
* @def SPEED_MIN
* @brief Minimum speed value used to turn the motors backwards to their maximum
*/
#define SPEED_MIN (-SPEED_DELTA)

/**
* @def SPEED_MAX
* @brief Maximum speed value used to turn the motors forwards to their maximum
*/
#define SPEED_MAX (SPEED_DELTA)



/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn motors_init
* @brief Initializes motors drivers 
* @param void
* @return void
*/
void motors_init(void) {
     PWM_Init(TIMx,CH,Frequence_Hz);
     Active_Complementary_Output(TIMx,CH);
	  PWM_Port_Init(TIMx,CH);
     PWM_Set_Duty_Cycle(TIMx,CH,0.5);

     //Enable Pin
     Port_IO_Clock_Enable(GPIOx);
     Port_IO_Init_Output(GPIOx,ENABLE_PIN);
     Port_IO_Reset(GPIOx,ENABLE_PIN);
   
     PWM_Enable(TIMx);
}

/**
* @fn motor_set_speed
* @brief Set motors speed 
* @param speed : Speed sent to the motors between -1 and +1
* @return void
*/
void motor_set_speed(float speed){
   float duty_cycle;

   if(speed > SPEED_MAX)      speed = SPEED_MAX;
   else if(speed < SPEED_MIN) speed = SPEED_MIN;
   
   duty_cycle = (PWM_DELTA_MAX)/(SPEED_DELTA) * speed + PWM_ZERO;
   PWM_Set_Duty_Cycle(TIMx,CH,duty_cycle);
}

/**
* @fn motors_start
* @brief Allows car departure with previously selected speed 
* @param void
* @return void
*/
void motors_start(void){
     Port_IO_Set(GPIOx,ENABLE_PIN);
}

/**
* @fn motors_stop
* @brief Stops the car 
* @param void
* @return void
*/
void motors_stop(void){
     Port_IO_Reset(GPIOx,ENABLE_PIN);
}
