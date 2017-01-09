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

#include <stm32f10x_tim.h>

/********************************/
/*         CONSTANTS            */
/********************************/

/**
* @def TIMx
* @brief Timer used to motors PWM generation
*/
#define TIMx TIM1

/**
* @def TIMx
* @brief Timer used to motors PWM generation
*/
#define TIMx_FRONT TIM1

/**
* @def CH
* @brief Channel used to motors PWM generation
*/
#define CH TIM_Channel_1

/**
* @def CH_FRONT
* @brief Channel used to front motor PWM generation
*/
#define CH_FRONT TIM_Channel_3

   
/**
* @def PWM_FREQUENCY
* @brief Period used to motors PWM generation in Hz
*/
#define PWM_FREQUENCY (20e3) //in Hz

/**
* @def GPIOx
* @brief GPIO used to enable the motors
*/
#define GPIOx GPIOC

/**
* @def GPIOx
* @brief GPIO used to enable the motors
*/
#define GPIOx_FRONT GPIOB

/**
* @def ENABLE_PIN
* @brief Pin used to enable the motors
*/
#define ENABLE_PIN GPIO_Pin_13

/**
* @def ENABLE_PIN_FRONT
* @brief Pin used to enable the motors
*/
#define ENABLE_PIN_FRONT GPIO_Pin_2

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

/**
* @def PWM_NUL
* @brief Set pwm duty cycle that keeps weels stopped
*/
#define PWM_NUL 0.5


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
   //PWM   
   pwm_init(TIMx,CH,PWM_FREQUENCY);
   pwm_port_init(TIMx, CH);
   active_complementary_output(TIMx, CH, REMAP_PIN);
   pwm_set_duty_cycle(TIMx, CH, PWM_NUL);

   //Enable Pin
   GPIO_QuickInit(GPIOx, ENABLE_PIN, GPIO_Mode_Out_PP);
   
   pwm_enable(TIMx);
}
/**
* @fn fron_motors_init
* @brief Initializes motors drivers 
* @param void
* @return void
*/
void front_motor_init(void) {
   //PWM   
   pwm_init(TIMx_FRONT,CH_FRONT,PWM_FREQUENCY);
   pwm_port_init(TIMx_FRONT, CH_FRONT);
   active_complementary_output(TIMx_FRONT, CH_FRONT, REMAP_PIN);
   pwm_set_duty_cycle(TIMx_FRONT, CH_FRONT, PWM_NUL);

   //Enable Pin
   GPIO_QuickInit(GPIOx_FRONT, ENABLE_PIN_FRONT, GPIO_Mode_Out_PP);
   pwm_enable(TIMx_FRONT);
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
* @fn front_motor_set_speed
* @brief Sets front motors speed(avaliable only for speed = LEFT(1) or RIGHT(-1))
* @param float speed 
* @return void
*/
void front_motor_set_speed(float speed){
   float duty_cycle;

        if(speed >  SPEED_MAX) speed =  SPEED_MAX;//LEFT
   else if(speed < -SPEED_MAX) speed = -SPEED_MAX;//RIGHT

   duty_cycle = (PWM_DELTA_MAX)/(SPEED_DELTA) * speed + PWM_ZERO;
   pwm_set_duty_cycle(TIMx_FRONT,CH_FRONT,duty_cycle);
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
* @fn front_motor_start
* @brief Allows car departure with previously selected speed 
* @param void
* @return void
*/
void front_motor_start(void){
   GPIO_SetBits(GPIOx_FRONT, ENABLE_PIN_FRONT);
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

/**
* @fn front_motor_stop
* @brief Stops the front motor 
* @param void
* @return void
*/
void front_motor_stop(void){
   GPIO_ResetBits(GPIOx_FRONT, ENABLE_PIN_FRONT);
}
