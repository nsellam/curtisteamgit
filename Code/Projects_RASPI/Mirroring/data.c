/**
 * @file data.c
 * @author Curtis Team
 * @brief functions for initialization of sensors and actuators
 */

#include "data.h"

#include <stddef.h>

#define INITIAL_8B_VALUE      0x00
#define INITIAL_FLOAT_VALUE   0.0

/************************
 *      VARIABLES       *
 ************************/
/**
 * @var volatile data_STM_t data_STM
 * @brief STM32 data
 */
volatile data_STM_t data_STM;
/**
 * @var volatile data_STM_t *pdata_STM
 * @brief STM32 data
 */
volatile data_STM_t *pdata_STM = &data_STM;
/**
 * @var volatile data_PI_t data_PI
 * @brief PI data
 */
volatile data_PI_t data_PI;
/**
 * @var volatile data_PI_t *pdata_PI
 * @brief PI data
 */
volatile data_PI_t *pdata_PI = &data_PI;

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn init_data_PI
 * @brief initializes the data_PI structure with bytes of zeros
 * @return void
 */
void init_data_PI(void);

/**
 * @fn init_data_STM
 * @brief initializes the data_STM structure with bytes of zeros
 * @return void
 */
void init_data_STM(void);


/**
* @fn init_data
* @brief initializes the data_PI and data_STM structures
* @return void
*/

void init_data(void) {
   init_data_PI();
   init_data_STM();
}

/**
 * @fn init_data_STM
 * @brief initializes the data_STM structure with bytes of zeros
 * @return void
 */
void init_data_STM(void) {
   int i;

   for(i = 0; i < DATA_STM_US_NUM; i++)
      data_STM.ultrasonic_sensors[i] = INITIAL_8B_VALUE;

   data_STM.wheel_position_sensor_R = INITIAL_8B_VALUE;
   data_STM.wheel_position_sensor_L = INITIAL_8B_VALUE;
   data_STM.steering_stop_sensor_R  = INITIAL_8B_VALUE;
   data_STM.steering_stop_sensor_L  = INITIAL_8B_VALUE;
   data_STM.errors_SPI              = INITIAL_8B_VALUE;
	data_STM.car_speed					= INITIAL_FLOAT_VALUE;
	data_STM.travelled_distance		= INITIAL_FLOAT_VALUE;
}

/**
 * @fn init_data_PI
 * @brief initializes the data_PI structure with bytes of zeros
 * @return void
 */
void init_data_PI(void) {
   data_PI.motor_prop = INITIAL_8B_VALUE;
   data_PI.motor_dir  = INITIAL_8B_VALUE;
   data_PI.led        = INITIAL_8B_VALUE;
   data_PI.errors_SPI = INITIAL_8B_VALUE;
}
