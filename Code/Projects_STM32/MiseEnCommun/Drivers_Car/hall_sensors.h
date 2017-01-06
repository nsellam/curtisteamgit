/**
 * @file    hall_sensors.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle hall sensors
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HALL_SENSORS_H
#define _HALL_SENSORS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @brief Identifier associated to the left hall sensor
*/
#define HALL_IDENTIFIER_L                       0x00

/**
 * @brief Identifier associated to the right hall sensor
*/
#define HALL_IDENTIFIER_R                       0x01

/**
 * @brief Number of hall sensors available
*/
#define HALL_SENSOR_NUMBER                      2

/**
 * @brief Number of the exti-line corresponding to the left hall sensor
*/
#define HALL_SENSOR_L_LINE                      EXTI_Line8

/**
 * @brief Number of the exti-line corresponding to the right hall sensor
*/
#define HALL_SENSOR_R_LINE                      EXTI_Line9

/**
 * @brief Number of the pin where the left hall sensor is plugged
*/
#define HALL_SENSOR_L_PIN                       GPIO_Pin_8

/**
 * @brief Number of the pin where the right hall sensor is plugged
*/
#define HALL_SENSOR_R_PIN                       GPIO_Pin_9

/**
 * @brief Pointer on the GPIO port interfacing the left hall sensor
*/
#define HALL_SENSOR_L_GPIO                      GPIOC

/**
 * @brief Pointer on the GPIO port interfacing the right hall sensor
*/
#define HALL_SENSOR_R_GPIO                      GPIOC

/**
 * @brief Way to trigg interrupts to detect forward movement
*/
#define HALL_SENSOR_TRIGG_FW                    EXTI_Trigger_Rising

/**
 * @brief Way to trigg interrupts to detect backward movement
*/
#define HALL_SENSOR_TRIGG_BW                    EXTI_Trigger_Falling

/**
 * @brief EXTI preemption priority
*/
#define HALL_SENSOR_PRIO                        1

/**
 * @brief Number of date of interrupt saved. Must be inferior to 0xFFFFFFFF
*/
#define HALL_SENSOR_MAX_SAVED_POP 			    36

/**
 * @def HALL_SENSOR_NUMBER_OF_SECTORS
 * @brief Number of fronts to count to get one full lap of wheel
*/ 
#define HALL_SENSOR_NUMBER_OF_SECTORS		    36

/**
 * @def ERROR_SENSOR_OUT_RANGE
 * @brief An error occured : current sector if superior to number of sectors 
*/ 
#define ERROR_SENSOR_OUT_OF_RANGE 	            (uint16_t)(-1)

/**
 * @def ERROR_VALUE_NOT_FOUND
 * @brief An error occured : this value was not computed (too few pops are kept in memory)
*/ 
#define ERROR_VALUE_NOT_FOUND 	                (uint64_t)(-1)

/**
 * @brief Time corresponding to a hall sensor period : meaning time between two changes of speed. Expressed in ms. 
*/
#define HALL_SENSOR_TIME_BETWEEN_TWO_UPDATES    1000

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void HallSensor_init(uint8_t hall_identifier);
void HallSensor_count(uint8_t hall_identifier);
void HallSensor_decount(uint8_t hall_identifier);
void HallSensor_Callback(uint8_t hall_identifier);
uint16_t HallSensor_getSector(uint8_t hall_identifier);
int32_t HallSensor_getLap(uint8_t hall_identifier);
uint64_t HallSensor_getLastPop(uint8_t n, uint8_t hall_identifier);
int8_t HallSensor_getNumberTicksInPeriod(uint8_t hall_identifier);
void HallSensor_CallbackOnFront(uint8_t hall_identifier);
void HallSensor_CallbackOnTimeOut(void);
#endif // _HALL_SENSORS_H
