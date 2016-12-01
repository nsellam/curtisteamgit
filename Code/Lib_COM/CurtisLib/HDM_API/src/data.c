/**
 * @file data.c
 * @author Curtis Team
 * @brief functions for initialization of sensors and actuators
 */

#include "data.h"

#include <stddef.h>

/************************
 *      VARIABLES       *
 ************************/

/**
 * @var volatile Data_PI_t *pData_PI
 * @brief PI Data
 */
volatile Data_PI_t *pData_PI = NULL;

/**
 * @var volatile Data_STM_t *pData_STM
 * @brief STM Data
 */
volatile Data_STM_t *pData_STM = NULL;

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn Data_Init_PI
 * @brief initializes the Data_PI structure pointed by pData_PI with the default values
 * @return void
 */
void Data_Init_PI(void) {
   pData_PI->motor_prop = 0;
   pData_PI->motor_dir  = 0;
   pData_PI->led        = 0;
   pData_PI->errors_SPI = 0;
}

/**
 * @fn Data_Init_STM
 * @brief initializes the Data_STM structure pointed by pData_STM with the default values
 * @return void
 */
void Data_Init_STM(void) {
   int i;

   for(i = 0; i < DATA_STM_US_NUM; i++)
      pData_STM->ultrasonic_sensors[i] = 0;

   pData_STM->wheel_position_sensor_R = 0;
   pData_STM->wheel_position_sensor_L = 0;
   pData_STM->steering_stop_sensor_R  = 0;
   pData_STM->steering_stop_sensor_L  = 0;
   pData_STM->errors_SPI              = 0;

	pData_STM->car_speed					  = 0.0;
	pData_STM->travelled_distance		  = 0.0;
}
