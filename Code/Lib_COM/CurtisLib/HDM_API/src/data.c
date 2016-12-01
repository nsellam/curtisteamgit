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
 * @var volatile data_PI_t *pdata_PI
 * @brief PI data
 */
volatile data_PI_t *pdata_PI = NULL;

/**
 * @var volatile data_STM_t *pdata_STM
 * @brief STM data
 */
volatile data_STM_t *pdata_STM = NULL;

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @brief initializes the data_PI structure pointed by pdata_PI with the default values
 * @return void
 */
void data_init_PI(void) {
   pdata_PI->motor_prop = 0;
   pdata_PI->motor_dir  = 0;
   pdata_PI->led        = 0;
   pdata_PI->errors_SPI = 0;
}

/**
 * @brief initializes the data_STM structure pointed by pdata_STM with the default values
 * @return void
 */
void data_init_STM(void) {
   int i;

   for(i = 0; i < DATA_STM_US_NUM; i++)
      pdata_STM->ultrasonic_sensors[i] = 0;

   pdata_STM->wheel_position_sensor_R = 0;
   pdata_STM->wheel_position_sensor_L = 0;
   pdata_STM->steering_stop_sensor_R  = 0;
   pdata_STM->steering_stop_sensor_L  = 0;
   pdata_STM->errors_SPI              = 0;

	pdata_STM->car_speed					  = 0.0;
	pdata_STM->travelled_distance		  = 0.0;
}
