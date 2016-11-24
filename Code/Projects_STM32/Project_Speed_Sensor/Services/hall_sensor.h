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
#define HALL_SENSOR_GPIO *GPIOC

/**
 * @def HALL_SENSOR_MODE
 * @brief Way to trigg interrupts for this sensor
*/
#define HALL_SENSOR_TRIGG EXTI_Trigger_Rising 

/**
 * @def HALL_SENSOR_MODE
 * @brief Mode of exti for this sensor
*/
#define HALL_SENSOR_MODE EXTI_Mode_Interrupt

/**
 * @def HALL_SENSOR_PRIO
 * @brief Mode of exti for this sensor
*/
#define HALL_SENSOR_PRIO 0

/**
 * @def HALL_SENSOR_SUBPRIO
 * @brief Mode of exti for this sensor
*/
#define HALL_SENSOR_SUBPRIO 0

/**
 * @def HALL_SENSOR_MAX_SAVED_POP
 * @brief Number of date of interrupt saved. Must be inferior to 0xFFFFFFFF
*/
#define HALL_SENSOR_MAX_SAVED_POP 			0xFF

/**
 * @def HALL_SENSOR_NUMBER_OF_SECTORS
 * @brief Number of fronts to count to get one full lap of wheel
*/
#define HALL_SENSOR_NUMBER_OF_SECTORS		36

/**
 * @def ERROR_SENSOR_OUT_RANGE
 * @brief An error occured : current sector if superior to number of sectors 
*/ 
#define ERROR_SENSOR_OUT_OF_RANGE 	0xFFFF

/**
 * @def ERROR_VALUE_NOT_FOUND
 * @brief An error occured : this value was not computed (too few pops are kept in memory)
*/ 
#define ERROR_VALUE_NOT_FOUND 	0xFFFFFFFFFFFFFFFF

/**
 * @def ONE_MORE_LAP
 * @brief The last hall sensor pop produces a new full lap
*/
#define ONE_MORE_LAP		1

/**
 * @fn hall_sensor_callback
 * @brief 
 * @return 
 * @retval 
*/
int hall_sensor_callback (void);

/**
 * @fn hall_sensor_callback
 * @brief 
 * @param 
 * @return 
 * @retval 
*/
uint64_t get_hall_sensor_last_pop (uint8_t);

/**
 * @fn get_hall_sensor_sector
 * @brief 
 * @param 
 * @return 
 * @retval 
*/
uint16_t hall_sensor_get_sector (void);

/**
 * @fn hall_sensor_get_lap
 * @brief 
 * @param 
 * @return 
 * @retval 
*/
uint32_t hall_sensor_get_lap(void);

/**
 * @fn hall_sensor_init
 * @brief 
 * @param 
 * @return 
 * @retval 
*/
void hall_sensor_init(void);

#endif //HALL_SENSOR_H
