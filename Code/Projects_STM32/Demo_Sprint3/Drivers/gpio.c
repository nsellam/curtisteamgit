#include "gpio.h"

/**
 * @fn gpio_enable_clock
 * @brief Enable clock on the adequate GPIO
 * @param GPIO -> GPIO_TypeDef (port to switch on the clock)
*/
void gpio_enable_clock (GPIO_TypeDef *GPIO);

void gpio_init (GPIO_TypeDef *GPIO,  uint16_t Pin, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode) {
	GPIO_InitTypeDef GPIO_InitStruct; 
	
	gpio_enable_clock (GPIO);
	
	GPIO_InitStruct.GPIO_Pin = Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
	
	GPIO_Init(GPIO, &GPIO_InitStruct);
}

void gpio_enable_clock (GPIO_TypeDef *GPIO) {
	if (GPIO == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if (GPIO == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if (GPIO == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if (GPIO == GPIOD) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	}
	else if (GPIO == GPIOE) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	}
	else if (GPIO == GPIOF) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	}
	else if (GPIO == GPIOG) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
	}
	else {}
}
