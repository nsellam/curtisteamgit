/**
 * @file gpio.c
 * @author Curtis Team
 * @brief Functions to handle GPIO  
 */
 
#include "gpio.h"

/**
 * @fn GPIO_ClockEnable
 * @brief Enable clock on the adequate GPIO
 * @param GPIOx -> GPIO_TypeDef (port to switch on the clock)
*/
void GPIO_ClockEnable(GPIO_TypeDef *GPIOx);

void GPIO_QuickInit(GPIO_TypeDef *GPIOx, uint16_t pin, GPIOMode_TypeDef mode) {
	GPIO_InitTypeDef GPIO_InitStruct; 
	
	GPIO_ClockEnable(GPIOx);
	
	GPIO_InitStruct.GPIO_Pin = pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = mode;
	
	GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void GPIO_ClockEnable(GPIO_TypeDef *GPIOx) {
        if (GPIOx == GPIOA) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
   else if (GPIOx == GPIOB) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
   else if (GPIOx == GPIOC) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   else if (GPIOx == GPIOD) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
   else if (GPIOx == GPIOE) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
   else if (GPIOx == GPIOF) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
   else if (GPIOx == GPIOG) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
   else {}
}
