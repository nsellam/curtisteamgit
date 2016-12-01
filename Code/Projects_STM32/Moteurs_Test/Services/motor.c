/**
 * @file motor.h
 * @author Curtis team
 * @brief Service library that allows to manipulate motors
 */

/********************************/
/*       LIBRARIES              */
/********************************/
#include "motor.h"

#include <stdint.h>

#include "gpio.h"
#include "timer.h"
#include "pwm.h"


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
#define MOTORS_FREQUENCY_Hz (float)(20e3) //in Hz
   
/**
* @def PWM_PERIOD
* @brief Period used to motors PWM generation in Hz
*/
#define PWM_PERIOD (float) 1/MOTORS_FREQUENCY_Hz //in Hz

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
* @def REMAP_PIN
* @brief Enables pin remap
*/
#define REMAP_PIN 0x1



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
   pwm_init(TIMx,CH,PWM_PERIOD);
   active_complementary_output(TIMx, CH, REMAP_PIN);
   pwm_port_init(TIMx, CH);
   pwm_set_duty_cycle(TIMx, CH, 0.5);

   //Enable Pin
   //GPIO_QuickInit(GPIOx, ENABLE_PIN, GPIO_Mode_Out_PP);

   pwm_enable(TIMx);
}

/**
* @fn motor_set_speed
* @brief Sets motors speed 
* @param float speed 
* @return void
*/
void motor_set_speed(float speed){
   float duty_cycle;

        if(speed >  SPEED_MAX) speed =  SPEED_MAX;
   else if(speed < -SPEED_MAX) speed = -SPEED_MAX;

   duty_cycle = (PWM_DELTA_MAX)/(SPEED_DELTA) * speed + PWM_ZERO;
   pwm_set_duty_cycle(TIMx,CH,duty_cycle);
}

/**
* @fn motors_start
* @brief Allows car departure with previously selected speed 
* @param void
* @return void
*/
void motors_start(void){
   GPIO_SetBits(GPIOx, ENABLE_PIN);
}

/**
* @fn motors_stop
* @brief Stops the car 
* @param void
* @return void
*/
void motors_stop(void){
   GPIO_ResetBits(GPIOx, ENABLE_PIN);
}
