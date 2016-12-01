#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include <stm32f10x.h>

/**
 * @def HALL_SENSOR_LINE
 * @brief Number of the exti-line corresponding to the hall sensor
*/
#define HALL_SENSOR_LINE EXTI_Line8

/**
 * @def HALL_SENSOR_PIN
 * @brief Number of the pin where the hall sensor is plugged
*/
#define HALL_SENSOR_PIN GPIO_Pin_8

/**
 * @def HALL_SENSOR_GPIO
 * @brief Pointer on the GPIO port interfacing the hall sensor
*/
#define HALL_SENSOR_GPIO GPIOC

/**
 * @def HALL_SENSOR_MODE
 * @brief Way to trigg interrupts for this sensor
*/
#define HALL_SENSOR_TRIGG EXTI_Trigger_Rising

/**
 * @def HALL_SENSOR_PRIO
 * @brief EXTI preemption priority
*/
#define HALL_SENSOR_PRIO 1

/**
 * @def HALL_SENSOR_MAX_SAVED_POP
 * @brief Number of date of interrupt saved. Must be inferior to 0xFFFFFFFF
*/
#define HALL_SENSOR_MAX_SAVED_POP 			0x0A

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
*/
void hall_sensor_callback (void);

/**
 * @fn get_hall_sensor_last_pop
 * @brief Return the date (in microseconds) of the last - n detection of the hall sensor. 
 * @param n -> uint8_t (number of the sample wanted)
 * @return uint64_t time of the detection passed as parameter
 * @retval time if it is possible to found it, ERROR_VALUE_NOT_FOUND if not
*/
uint64_t get_hall_sensor_last_pop (uint8_t n);

/**
 * @fn get_hall_sensor_sector
 * @brief Return the current sector
 * @return uint16_t -> curent sector
 * @retval Current sector if current sector is under number of sectors, ERROR_SENSOR_OUT_OF_RANGE if not.
*/
uint16_t hall_sensor_get_sector (void);

/**
 * @fn hall_sensor_get_lap
 * @brief Return the current lap
 * @return uint16_t -> curent lap
*/
uint32_t hall_sensor_get_lap(void);

/**
 * @fn hall_sensor_init
 * @brief Initialize hall sensor
*/
void hall_sensor_init(void);

#endif //HALL_SENSOR_H
