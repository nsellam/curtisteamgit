/**
 * @file systick.c
 * @author Curtis Team
 * @brief Functions to handle systick (STM internal time)  
 */

#include "systick.h"

/**
 * @var time_micros 
 * @brief Current STM32 time (expressed in microseconds)
*/
static uint64_t time_micros;

void systick_init(void) {
  time_micros = 0;
	while (SysTick_Config(SystemCoreClock / SYSTICK_FREQ - 1) != 0);
	NVIC_SetPriority(SysTick_IRQn, 1);
}

uint64_t micros(void) {
  return time_micros*1000;
}

void systick_inc(void) {
  time_micros++;
}
