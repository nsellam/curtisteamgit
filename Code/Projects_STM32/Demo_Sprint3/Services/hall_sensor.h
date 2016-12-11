/**
 * @file hall_sensor.h
 * @author Curtis Team
 * @brief Handlers of service functions for hall sensors
 */

#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include <stm32f10x.h>

/**
 * @def HALL_IDENTIFIER_L
 * @brief Identifier associated to the left hall sensor
*/
#define HALL_IDENTIFIER_L 0x00

/**
 * @def HALL_IDENTIFIER_R
 * @brief Identifier associated to the right hall sensor
*/
#define HALL_IDENTIFIER_R 0x01

/**
 * @def HALL_SENSOR_NUMBER
 * @brief Identifier associated to the right hall sensor
*/
#define HALL_SENSOR_NUMBER 2

/**
 * @def HALL_SENSOR_L_LINE
 * @brief Number of the exti-line corresponding to the left hall sensor
*/
#define HALL_SENSOR_L_LINE EXTI_Line8

/**
 * @def HALL_SENSOR_R_LINE
 * @brief Number of the exti-line corresponding to the right hall sensor
*/
#define HALL_SENSOR_R_LINE EXTI_Line9

/**
 * @def HALL_SENSOR_L_PIN
 * @brief Number of the pin where the left hall sensor is plugged
*/
#define HALL_SENSOR_L_PIN GPIO_Pin_8

/**
 * @def HALL_SENSOR_R_PIN
 * @brief Number of the pin where the right hall sensor is plugged
*/
#define HALL_SENSOR_R_PIN GPIO_Pin_9

/**
 * @def HALL_SENSOR_L_GPIO
 * @brief Pointer on the GPIO port interfacing the left hall sensor
*/
#define HALL_SENSOR_L_GPIO GPIOC

/**
 * @def HALL_SENSOR_R_GPIO
 * @brief Pointer on the GPIO port interfacing the right hall sensor
*/
#define HALL_SENSOR_R_GPIO GPIOC

/**
 * @def HALL_SENSOR_TRIGG_FW
 * @brief Way to trigg interrupts to detect forward movement
*/
#define HALL_SENSOR_TRIGG_FW EXTI_Trigger_Rising

/**
 * @def HALL_SENSOR_TRIGG_BW
 * @brief Way to trigg interrupts to detect backward movement
*/
#define HALL_SENSOR_TRIGG_BW EXTI_Trigger_Falling

/**
 * @def HALL_SENSOR_PRIO
 * @brief EXTI preemption priority
*/
#define HALL_SENSOR_PRIO 1

/**
 * @def HALL_SENSOR_MAX_SAVED_POP
 * @brief Number of date of interrupt saved. Must be inferior to 0xFFFFFFFF
*/
#define HALL_SENSOR_MAX_SAVED_POP 			36

/**
 * @def HALL_SENSOR_NUMBER_OF_SECTORS
 * @brief Number of fronts to count to get one full lap of wheel
*/
#define HALL_SENSOR_NUMBER_OF_SECTORS		36

/**
 * @def ERROR_SENSOR_OUT_RANGE
 * @brief An error occured : current sector if superior to number of sectors 
*/ 
#define ERROR_SENSOR_OUT_OF_RANGE 	(uint16_t)(-1)

/**
 * @def ERROR_VALUE_NOT_FOUND
 * @brief An error occured : this value was not computed (too few pops are kept in memory)
*/ 
#define ERROR_VALUE_NOT_FOUND 	(uint64_t)(-1)

/**
 * @fn hall_sensor_callback
 * @brief Called function on external interrupt (EXTI). Must not be call by user. 
 * @param hall_identifier : hall sensor front detected. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R
*/
void hall_sensor_callback (uint8_t hall_identifier);

/**
 * @fn get_hall_sensor_last_pop
 * @brief Return the date (in milliseconds) of the last - n detection of the hall sensor. 
 * @param n -> uint8_t (number of the sample wanted)
 * @param hall_identifier -> uint8_t (number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R)
 * @return uint64_t time of the detection passed as parameter
 * @retval time if it is possible to found it, ERROR_VALUE_NOT_FOUND if not
*/
uint64_t hall_sensor_get_last_pop (uint8_t n, uint8_t hall_identifier);

/**
 * @fn get_hall_sensor_sector
 * @brief Return the current sector
 * @return uint16_t -> curent sector
 * @retval Current sector if current sector is under number of sectors, ERROR_SENSOR_OUT_OF_RANGE if not.
*/
uint16_t hall_sensor_get_sector (uint8_t hall_identifier);

/**
 * @fn hall_sensor_get_lap
 * @param hall_identifier -> uint8_t (number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R)
 * @brief Return the current lap for the hall sensor considered
 * @return uint16_t -> curent lap
*/
int32_t hall_sensor_get_lap(uint8_t hall_identifier);

/**
 * @fn hall_sensor_init
 * @param hall_identifier -> uint8_t (number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R)
 * @param direction -> uint8_t (car direction)
 * @brief Reset and start specified hall sensor 
*/
void hall_sensor_init(uint8_t hall_identifier, uint8_t direction);

/**
 * @fn hall_sensor_start
 * @param hall_identifier -> uint8_t (number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R)
 * @param direction -> uint8_t (car direction)
 * @brief Only start specified hall sensor 
*/
void hall_sensor_start(uint8_t hall_identifier, uint8_t direction);

/**
 * @fn hall_sensor_count_peridod_laps
 * @brief Count the number of ticks detected during one period
*/
void hall_sensor_count_peridod_ticks (void);

/**
 * @fn hall_sensor_get_lap
 * @param hall_identifier -> uint8_t (number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R)
 * @brief Return the number of ticks detected during the last hall sensor period
 * @return uint8_t -> number of ticks during previous period for the hall sensor considered
*/
int8_t hall_sensor_get_number_ticks_in_period (uint8_t hall_identifier);

#endif //HALL_SENSOR_H
