/**
 * @file exti.h
 * @author Curtis Team
 * @brief Headers of functions to handle external interrupts (EXTI)  
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _EXTI_H
#define _EXTI_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>
#include "gpio.h"
#include "nvic.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @def EXTI_NO_ERROR
 * @brief Given pin was succesfully initialize as external interruption
*/
#define EXTI_NO_ERROR                  0

/**
 * @def EXTI_ERROR_INVALID_LINE
 * @brief Given pin couldn't be initialize as external interruption due to a non valid line
*/ 
#define EXTI_ERROR_INVALID_LINE        -1

/**
 * @def EXTI_ERROR_INVALID_CHANNEL
 * @brief Given pin couldn't be initialize as external interruption due to a problem while computing channel
*/ 
#define EXTI_ERROR_INVALID_CHANNEL     -2

/**
 * @def EXTI_ERROR_INVALID_PORT_SOURCE
 * @brief Given port couldn't be found
*/ 
#define EXTI_ERROR_INVALID_PORT_SOURCE -3

/**
 * @def EXTI_ERROR_INVALID_PIN_SOURCE
 * @brief Given pin couldn't be found
*/ 
#define EXTI_ERROR_INVALID_PIN_SOURCE  -4

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int EXTI_QuickInit(GPIO_TypeDef *GPIOx, uint16_t pin, EXTITrigger_TypeDef trigger, uint8_t priority);

#endif // _EXTI_H
