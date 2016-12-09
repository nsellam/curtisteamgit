/**
 * @file systick.h
 * @author Curtis Team
 * @brief Headers of functions to handle systick (STM internal time)  
 */

#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stm32f10x.h>

/**
 * @def SYSTICK_FREQ 
 * @brief Frequency to count systicks 
*/
//#define SYSTICK_FREQ  1000000 // Hz
#define SYSTICK_FREQ  1000 // Hz

/**
 * @fn systick_init
 * @brief Initializes systick system 
*/
void systick_init(void);

/**
 * @fn millis
 * @brief Returns the current STM32 time
 * @return uint64_t (time elapsed since systick initialization expressed in milliseconds) 
*/
uint64_t millis(void);

/**
 * @fn systick_inc
 * @brief Increments current time. NOT SUPPOSED TO BE USE OUT OF SysTick_Handler (in stm32f10x_it.c).
*/
void systick_inc(void);

#endif //SYSTICK_H
