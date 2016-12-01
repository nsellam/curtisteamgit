#include "systick.h"

/**
 * @var time_micros 
 * @brief Current STM32 time (expressed in microseconds)
*/
static uint64_t time_micros;

void systick_init(void) {
  time_micros = 0;
	while (SysTick_Config(SystemCoreClock / SYSTICK_FREQ - 1) != 0);
	NVIC_SetPriority(SysTick_IRQn, 0);
}

uint64_t micros(void) {
  return time_micros;
}

void systick_inc(void) {
  time_micros++;
}
