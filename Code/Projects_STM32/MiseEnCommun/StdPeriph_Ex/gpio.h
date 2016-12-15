/**
 * @file	gpio.h
 * @author	Curtis Team
 * @brief	Headers of functions to handle GPIO  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GPIO_H
#define _GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GPIO_QuickInit(GPIO_TypeDef *GPIOx, uint16_t pin, GPIOMode_TypeDef mode);

#endif // _GPIO_H
