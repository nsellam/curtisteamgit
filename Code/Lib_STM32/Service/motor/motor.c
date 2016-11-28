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
#include <gpio.h>
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
#define Frequence_Hz 2.0e4 //in Hz

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
* @def PWM_min
* @brief Min value used in motors
*/
#define PWM_min 0.245

/**
* @def PWM_max
* @brief Max value used in motors
*/
#define PWM_max 0.754




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

     //Enable Pin
     Port_IO_Clock_Enable(GPIOx);
     Port_IO_Init_Output(GPIOx,ENABLE_PIN);
}

/**
* @fn motor_set_speed
* @brief Set motors speed 
* @param speed : Speed sent to the motors between -1 and +1
* @return void
*/
void motor_set_speed(float speed){
     float duty_cycle = 0.5*speed + 0.5;
     if(duty_cycle >= PWM_min && duty_cycle <= PWM_max){
        PWM_Set_Duty_Cycle(TIMx,CH,duty_cycle);
     }
     else{
        if(speed>0)
           PWM_Set_Duty_Cycle(TIMx,CH,PWM_max);
        else
           PWM_Set_Duty_Cycle(TIMx,CH,PWM_min);
     }
}

/**
* @fn motors_start
* @brief Allows car departure with previously selected speed 
* @param void
* @return void
*/
void motors_start(void){
     PWM_Enable(TIMx);
     Port_IO_Set(GPIOx,ENABLE_PIN);
}

/**
* @fn motors_stop
* @brief Stops the car 
* @param void
* @return void
*/
void motors_stop(void){
     PWM_Set_Duty_Cycle(TIMx,CH,0); 
}
