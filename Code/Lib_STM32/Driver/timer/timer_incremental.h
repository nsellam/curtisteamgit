#ifndef _TIMER_INCREMENTAL_H_
#define _TIMER_INCREMENTAL_H_

#include <stm32f10x.h>

void Timer_Inc_Init(TIM_TypeDef *Timer);
int Get_Nb_Interrupt(void);
void Set_Nb_Interrupt(int n);

#endif // _TIMER_INCREMENTAL_H_
