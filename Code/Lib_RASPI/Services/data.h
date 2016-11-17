#ifndef DATA_H
#define DATA_H

/**
 * @file data.h
 * @author Curtis Team
 * @brief header for data.c, contains structures of sensors and actuators

#include <stdint.h>

/************************
 *     STRUCTURES       *
 ************************/

/**
 * @struct data_STM
 * @brief data updated by the STM32
 * size: 11 bytes
 */
typedef struct data_STM {
  uint8_t ultrasonic_sensors[6];
  uint8_t wheel_position_sensor_R;
  uint8_t wheel_position_sensor_L;
  uint8_t steering_stop_sensor_R;
  uint8_t steering_stop_sensor_L;
  uint8_t errors_SPI; 
} data_STM_t;

extern data_STM_t *pdata_STM;

/**
 * @struct data_Pi
 * @brief data updated by the Raspberry Pi
 * size: 4 bytes
 */
typedef struct data_Pi {
  uint8_t motor_prop;
  uint8_t motor_dir;
  uint8_t led;
  uint8_t errors_SPI; 
} data_Pi_t;

extern data_Pi_t *pdata_Pi;

/************************
 *      FUNCTIONS       *
 ************************/

/**
* @fn init_data_STM
* @brief initializes the data_STM structure 
* @return void
*/
void init_data_STM(void);

/**
* @fn init_data_Pi
* @brief initializes the data_Pi structure 
* @return void
*/
void init_data_Pi(void) ;

#endif
