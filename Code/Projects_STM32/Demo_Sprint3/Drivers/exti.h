#ifndef EXTI_H
#define EXTI_H

#include <stm32f10x.h>
#include "gpio.h"

/**
 * @def EXTI_NO_ERROR
 * @brief Given pin was succesfully initialize as external interruption
*/
#define EXTI_NO_ERROR										 0

/**
 * @def EXTI_ERROR_INVALID_LINE
 * @brief Given pin couldn't be initialize as external interruption due to a non valid line
*/ 
#define EXTI_ERROR_INVALID_LINE					-1

/**
 * @def EXTI_ERROR_INVALID_CHANNEL
 * @brief Given pin couldn't be initialize as external interruption due to a problem while computing channel
*/ 
#define EXTI_ERROR_INVALID_CHANNEL			-2

/**
 * @def EXTI_ERROR_INVALID_PORT_SOURCE
 * @brief Given port couldn't be found
*/ 
#define EXTI_ERROR_INVALID_PORT_SOURCE -3

/**
 * @def EXTI_ERROR_INVALID_PIN_SOURCE
 * @brief Given pin couldn't be found
*/ 
#define EXTI_ERROR_INVALID_PIN_SOURCE -4

/**
 * @fn exti_init
 * @brief Make the initialization of the given Pin to prepare it to produce external interuptions
 * @param GPIO -> GPIO_TypeDef (port of the pin to init)
 * @param Pin -> uint16_t (# of the pin to init)
 * @param EXTI_Mode -> EXTIMode_TypeDef (behaviour when interruption is raised : EXTI_Mode_Interrupt or EXTI_Mode_Event)
 * @param EXTITrigger -> EXTITrigger_TypeDef (type of fronts to consider : EXTI_Trigger_Rising, EXTI_Trigger_Falling, EXTI_Trigger_Rising_Falling)
 * @param Priority -> uint8_t (priority of the interrupt to generate)
 * @param SubPriority -> uint8_t (subpriority of the interrupt to generate)
 * @return int (error detected while computing initialization) 
 * @retval EXTI_NO_ERROR (no error), EXTI_ERROR_INVALID_LINE (line specified cannot be set to EXTI), EXTI_ERROR_INVALID_CHANNEL (a problem was found while computing channel associated to specify line)
*/
int exti_init (GPIO_TypeDef *GPIO, uint16_t Pin , EXTIMode_TypeDef EXTI_Mode, EXTITrigger_TypeDef EXTITrigger, uint8_t Priority, uint8_t SubPriority);

#endif //EXTI_H
