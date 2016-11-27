#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <stddef.h>

#define DATA_STM_US_NUM 6

#define DATA_SIZE_MAX ((sizeof(data_STM_t) > sizeof(data_PI_t)) ? sizeof(data_STM_t) : sizeof(data_PI_t))

/************************
 *     STRUCTURES       *
 ************************/

/**
 * @struct data_STM_t
 * @brief data updated by the STM32
 * size: 19 bytes
 */
typedef struct {
  uint8_t ultrasonic_sensors[DATA_STM_US_NUM];

  uint8_t wheel_position_sensor_R;
  uint8_t wheel_position_sensor_L;
  
  float travelled_distance; 
  float car_speed;

  uint8_t steering_stop_sensor_R;
  uint8_t steering_stop_sensor_L;

  uint8_t errors_SPI;
} data_STM_t;


/**
 * @struct data_PI_t
 * @brief data updated by the Raspberry Pi
 * size: 4 bytes
 */
typedef struct {
  uint8_t motor_prop;
  uint8_t motor_dir;
  uint8_t led;

  uint8_t errors_SPI;
} data_PI_t;

/************************
 *      VARIABLES       *
 ************************/

extern volatile data_STM_t *pdata_STM;
extern volatile data_PI_t *pdata_PI;

/************************
 *      FUNCTIONS       *
 ************************/

/**
* @fn init_data
* @brief initializes the data_PI and data_STM structures pointed by pdata_PI and pdata_STM
* @return void
*/

void init_data(void);

#endif // DATA_H
