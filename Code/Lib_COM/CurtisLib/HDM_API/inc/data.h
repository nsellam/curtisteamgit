#ifndef _DATA_H_
#define _DATA_H_

#include <stdint.h>

#define US_NUM 6

/************************
 *     STRUCTURES       *
 ************************/

/**
 * @struct data_STM
 * @brief data updated by the STM32
 * size: 11 bytes
 */
typedef struct {
  uint8_t ultrasonic_sensors[US_NUM];

  uint8_t wheel_position_sensor_R;
  uint8_t wheel_position_sensor_L;

  uint8_t steering_stop_sensor_R;
  uint8_t steering_stop_sensor_L;

  uint8_t errors_SPI;
} data_STM_t;

extern volatile data_STM_t *pdata_STM;


/**
 * @struct data_PI
 * @brief data updated by the Raspberry Pi
 * size: 4 bytes
 */
typedef struct {
  uint8_t motor_prop;
  uint8_t motor_dir;
  uint8_t led;

  uint8_t errors_SPI;
} data_PI_t;

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

#endif // _DATA_H_
