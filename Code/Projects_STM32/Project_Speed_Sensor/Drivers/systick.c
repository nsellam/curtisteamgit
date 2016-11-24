#include "systick.h"

void systick_init(void) {
  timeMicros = 0;
	while (SysTick_Config(SystemCoreClock / SYSTICK_FREQ - 1) != 0);
	NVIC_SetPriority(SysTick_IRQn, 0);
}

uint64_t micros(void) {
  return timeMicros;
}

void systick_inc(void) {
  timeMicros++;
}
