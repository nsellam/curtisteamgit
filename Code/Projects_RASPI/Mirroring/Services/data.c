/**
 * @file data.c
 * @author Curtis Team
 * @brief functions for initialization of sensors and actuators
 */

#include "data.h"

#define ZEROS_8 0x00

/************************
 *      VARIABLES       *
 ************************/

data_STM_t data_STM; 
data_STM_t *pdata_STM = &data_STM;

data_Pi_t data_Pi; 
data_Pi_t *pdata_Pi = &data_Pi;

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn init_data_STM
 * @brief initializes the data_STM structure with bytes of zeros 
 * @return void
 */
void init_data_STM(void) {
  data_STM.ultrasonic_sensors[0] = ZEROS_8;
  data_STM.ultrasonic_sensors[1] = ZEROS_8;
  data_STM.ultrasonic_sensors[2] = ZEROS_8;
  data_STM.ultrasonic_sensors[3] = ZEROS_8;
  data_STM.ultrasonic_sensors[4] = ZEROS_8;
  data_STM.ultrasonic_sensors[5] = ZEROS_8;
  data_STM.wheel_position_sensor_R = ZEROS_8; 
  data_STM.wheel_position_sensor_L = ZEROS_8;   
  data_STM.steering_stop_sensor_R = ZEROS_8;
  data_STM.steering_stop_sensor_L = ZEROS_8;
  data_STM.errors_SPI = ZEROS_8;
}

/**
* @fn init_data_Pi
* @brief initializes the data_Pi structure with bytes of zeros
* @return void
*/
void init_data_Pi(void) {
  data_Pi.motor_prop = ZEROS_8;
  data_Pi.motor_dir = ZEROS_8;
  data_Pi.led = ZEROS_8;
  data_Pi.errors_SPI = ZEROS_8;
}
