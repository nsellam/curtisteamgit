/**
 * @file systick.c
 * @author Curtis Team
 * @brief Functions to handle systick (STM internal time)  
 */

#include "systick.h"

/**
 * @var time_millis 
 * @brief Current STM32 time (expressed in milliseconds)
*/
static uint64_t time_millis;

void systick_init(void) {
  time_millis = 0;
	while (SysTick_Config(SystemCoreClock / SYSTICK_FREQ - 1) != 0);
	NVIC_SetPriority(SysTick_IRQn, 1);
}

uint64_t millis(void) {
  return time_millis;
}

void systick_inc(void) {
  time_millis++;
}
