#ifndef _TIMER_CAPTURE_H_
#define _TIMER_CAPTURE_H_

#include <stdint.h>
#include <stm32f10x.h>
#include <timer.h>
#include <gpio.h>

void compare_output_init(TIM_TypeDef *Timer, uint8_t Channel, float Frequence_PWM_Hz);

void compare_output_start(TIM_TypeDef *Timer, uint8_t Channel);

void TIM_Capt_Init(TIM_TypeDef *Timer, uint8_t Channel);

void PWM_In_Mode_TI1(TIM_TypeDef *Timer);
void PWM_In_Mode_TI2(TIM_TypeDef *Timer);

void PWM_In_Mode_Port_Clock_Init(TIM_TypeDef *Timer);

uint16_t GetCaptureVal(TIM_TypeDef *Timer, uint8_t Channel);

#endif // _TIMER_CAPTURE_H_
