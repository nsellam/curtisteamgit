/**
 * @file	gpio.c
 * @author	Curtis Team
 * @brief	Functions to handle GPIO  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void GPIO_ClockEnable(GPIO_TypeDef *GPIOx);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief     Makes the initialization of the given Pin with the parameters specified
 * @param     GPIOx GPIO_TypeDef (port of the pin to init)
 * @param     pin uint16_t (# of the pin to init)
 * @param     mode GPIOMode_TypeDef (mode of GPIO => GPIO_Mode_AIN, GPIO_Mode_IN_FLOATING, GPIO_Mode_IPD, GPIO_Mode_IPU, GPIO_Mode_Out_OD, GPIO_Mode_Out_PP, GPIO_Mode_AF_OD, GPIO_Mode_AF_PP8)
 * @retval     None
 */
void GPIO_QuickInit(GPIO_TypeDef *GPIOx, uint16_t pin, GPIOMode_TypeDef mode) {
    GPIO_InitTypeDef GPIO_InitStruct; 
    
    GPIO_ClockEnable(GPIOx);
    
    GPIO_InitStruct.GPIO_Pin = pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = mode;
    
    GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief     Enables clock on the adequate GPIO
 * @param     GPIOx GPIO_TypeDef (port to switch on the clock)
 * @retval     None
*/
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
