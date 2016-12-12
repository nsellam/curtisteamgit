
#include <stdint.h>
#include <stm32f10x.h>
#include "timer.h"
#include "gpio.h"

#define CAPTURE_GPIO_MODE GPIO_Mode_IN_FLOATING


void Capture_Init(TIM_TypeDef *timer, uint16_t channel, float frequency_compare_Hz);

void Capture_Enable(TIM_TypeDef *timer);

void Capture_Disable(TIM_TypeDef *timer);

void Capture_PortInit(TIM_TypeDef *timer, uint16_t channel);

void Capture_ITEnable(TIM_TypeDef *timer, uint16_t channel, uint8_t priority, void (*IT_function)(void));

