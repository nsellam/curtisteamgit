#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <stddef.h>

#define DATA_STM_US_NUM 6

#define DATA_ALIGNMENT_PI  4
#define DATA_SIZE_MAX_RAW  ((sizeof(data_STM_t) > sizeof(data_PI_t)) ? sizeof(data_STM_t) : sizeof(data_PI_t))
#define DATA_SIZE_MAX      (DATA_SIZE_MAX_RAW - (DATA_ALIGNMENT_PI - DATA_SIZE_MAX_RAW % DATA_ALIGNMENT_PI) % DATA_ALIGNMENT_PI)

/************************
 *     STRUCTURES       *
 ************************/

/**
 * @struct data_STM_t
 * @brief data updated by the STM32
 * size: 19 bytes
 */
typedef struct {
   uint8_t ultrasonic_sensors[DATA_STM_US_NUM]; /*!< Ultrasonic sensors data */

   uint8_t wheel_position_sensor_R;				/*!< Returns position sensor data of right motor */
   uint8_t wheel_position_sensor_L;				/*!< Returns position sensor data of left motor */

   float travelled_distance;					/*!< Travelled distance data */
   float car_speed;

   uint8_t steering_stop_sensor_R;				/*!< Steering position data */
   uint8_t steering_stop_sensor_L;				/*!< Steering position data */

   uint8_t errors_SPI;							/*!< Errors of communication data */
} data_STM_t;


/**
 * @struct data_PI_t
 * @brief data updated by the Raspberry Pi
 * size: 4 bytes
 */
typedef struct {
  uint8_t motor_prop;							/*!< Propulsion motors data */
  uint8_t motor_dir;							/*!< Direction motor data */
  uint8_t led;									/*!< LED data */

  uint8_t errors_SPI;							/*!< Errors of communication data */
} data_PI_t;

/************************
 *      VARIABLES       *
 ************************/
/**
 * @var extern volatile data_STM_t
 * @brief STM32 data
 */
extern volatile data_STM_t *pdata_STM;
/**
 * @var extern volatile data_PI_t
 * @brief PI data
 */
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
