
#include <timer.h>
#include <stm32f10x_tim.h>
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <misc.h>


void capture_imput_init(TIM_TypeDef* timer, uint16_t channel, float period_us);

void capture_imput_start(TIM_TypeDef* timer, uint16_t channel);

