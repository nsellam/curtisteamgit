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
* @brief GPIO used to motors Enable generation
*/
#define GPIOx GPIOC

/**
* @def ENABLE_PIN
* @brief Pin used to motors Enable generation
*/
#define ENABLE_PIN 6

/**
* @def PWM_MIN
* @brief Min PWM value used in motors
*/
#define PWM_MIN (float)(0.245)

/**
* @def PWM_MAX
* @brief Max PWM value used in motors
*/
#define PWM_MAX (float)(0.754)

/**
* @def SPEED_MIN
* @brief Min speed in motors
*/
#define SPEED_MIN (float)(-1.0)

/**
* @def SPEED_MAX
* @brief Max speed in motors
*/
#define SPEED_MAX (float)(1.0)



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
   
   duty_cycle = (PWM_MAX - PWM_MIN)/(SPEED_MAX - SPEED_MIN) * (speed - SPEED_MIN) + PWM_MIN;
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
