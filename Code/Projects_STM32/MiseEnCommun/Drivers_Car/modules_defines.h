/**
 * @file    modules_defines.h
 * @author  Curtis Team
 * @brief   Modules description
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MODULES_DEFINES_H
#define _MODULES_DEFINES_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @brief Identifier associated to the left hall sensor
*/
#define HALLSENSOR_IDENTIFIER_L                       0x00

/**
 * @brief Identifier associated to the right hall sensor
*/
#define HALLSENSOR_IDENTIFIER_R                       0x01

/**
 * @brief Number of hall sensors available
*/
#define HALLSENSOR_NUMBER                      2

/**
 * @brief Number of the exti-line corresponding to the left hall sensor
*/
#define HALLSENSOR_L_LINE                      EXTI_Line8

/**
 * @brief Number of the exti-line corresponding to the right hall sensor
*/
#define HALLSENSOR_R_LINE                      EXTI_Line9

/**
 * @brief Number of the pin where the left hall sensor is plugged
*/
#define HALLSENSOR_L_PIN                       GPIO_Pin_8

/**
 * @brief Number of the pin where the right hall sensor is plugged
*/
#define HALLSENSOR_R_PIN                       GPIO_Pin_9

/**
 * @brief Pointer on the GPIO port interfacing the left hall sensor
*/
#define HALLSENSOR_L_GPIO                      GPIOC

/**
 * @brief Pointer on the GPIO port interfacing the right hall sensor
*/
#define HALLSENSOR_R_GPIO                      GPIOC

/**
 * @def HALL_SENSOR_NUMBER_OF_SECTORS
 * @brief Number of fronts to count to get one full lap of wheel
*/ 
#define HALLSENSOR_NUMBER_OF_SECTORS		    36


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif // _MODULES_DEFINES_H
