#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include <stm32f10x.h>

#define SYSTICK_FREQ  1000000 // Hz

static uint64_t timeMicros;

void systick_init(void);
uint64_t micros(void);
void systick_inc(void);

#endif //SYSTICK_H
