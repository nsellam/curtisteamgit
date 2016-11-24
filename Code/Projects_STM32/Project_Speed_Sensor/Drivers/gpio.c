#include "gpio.h"

void gpio_init (GPIO_TypeDef *GPIO,  uint16_t Pin, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode) {
	GPIO_InitTypeDef GPIO_InitStruct; 
	GPIO_InitStruct.GPIO_Pin = Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
	
	GPIO_Init(GPIO, &GPIO_InitStruct);
}
