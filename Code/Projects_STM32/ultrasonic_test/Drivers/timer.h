/**
 * @file timer.h
 * @author Curtis team
 * @brief Driver library that allows to manipulate timers in STM32
 */


/**
* @def _TIMER_H_
* @brief to memorize if "timer.h" file has already been included
*/
#ifndef _TIMER_H_
#define _TIMER_H_


/********************************/
/*       LIBRARIES              */
/********************************/
#include <stm32f10x.h>


/********************************/
/*         CONSTANTS            */
/********************************/

/**
* @def US_PER_S
* @brief Number of microseconds per second
*/
#define US_PER_S  (1.0e+06)



/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn Timer_1234_Init
* @brief Initializes timers 1, 2, 3 or 4
* @param Timer Timer to be used
* @param period_us Timer period in microseconds  
* @return Period in microseconds obtained
*/
void timer_init (TIM_TypeDef *timer, float period_us);

/**
* @fn Timer_1234_ITEnable
* @brief Activates Overflow timer interruption and set function and spriority 
* @param Timer Timer to be used
* @param priority Priority of interruption
* @param IT_function run in interruption handling 
* @return void
*/
void timer_ITEnable(TIM_TypeDef *Timer, uint8_t priority, void (*IT_function)(void));

/**
* @fn Timer_1234_Enable
* @brief Enables timers 1, 2, 3 or 4
* @param Timer Timer to be used  
* @return void
*/
void timer_start(TIM_TypeDef *Timer);

/**
* @fn Timer_1234_Disable
* @brief Disables timers 1, 2, 3 or 4
* @param Timer Timer to be used  
* @return void
*/
void timer_disable(TIM_TypeDef *Timer);


/**
  * @fn RCC_timer_configuration
  * @brief  Configures the different system clocks.
  * @param  TIM_TypeDef *timer
  * @retval None
  */
void RCC_timer_configuration(TIM_TypeDef *timer);


#endif // _TIMER_H_
