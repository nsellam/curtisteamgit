/**
 * @file    data_interface.h
 * @author  Curtis Team
 * @brief   Headers of functions for initialization of sensors and actuators
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DATA_INTERFACE_H
#define _DATA_INTERFACE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DATA_STM_US_NUM             6

#define DATA_ALIGNMENT_PI           4
#define DATA_SIZE_MAX_RAW           ((sizeof(data_STM_t) > sizeof(data_PI_t)) ? sizeof(data_STM_t) : sizeof(data_PI_t))
#define DATA_SIZE_MAX               (DATA_SIZE_MAX_RAW - (DATA_ALIGNMENT_PI - DATA_SIZE_MAX_RAW % DATA_ALIGNMENT_PI) % DATA_ALIGNMENT_PI)

// Ultrasonic ID
/**
* @brief    US_FR : id of front right ultrasonic sensor
*/
#define US_FR 0x00

/**
* @brief    US_FM : id of front middle ultrasonic sensor
*/
#define US_FM 0x01

/**
* @brief    US_FL : id of front left ultrasonic sensor
*/
#define US_FL 0x02

/**
* @brief    US_BR : id of back right ultrasonic sensor
*/
#define US_BR 0x03

/**
* @brief    US_BM : id of back middle ultrasonic sensor
*/
#define US_BM 0x04
    
/**
* @brief    US_BL : id of back left ultrasonic sensor
*/
#define US_BL 0x05

// Wheel position sensors 
/**
* @brief    WP_R : id of Right wheel position sensor
*/
#define WP_R 0x00

/**
* @brief    WP_L : id of Left wheel position sensor
*/
#define WP_L 0x01

// Steering stop sensor
/**
* @brief    SS_R : id of Right wheel position sensor
*/
#define SS_R 0x00

/**
* @brief    SS_L : id of Left wheel position sensor
*/
#define SS_L 0x01

/**
 * @brief data updated by the STM32
 * size: 19 bytes
 */
typedef struct {
   uint8_t ultrasonic_sensors[DATA_STM_US_NUM]; /*!< Ultrasonic sensors data */

   uint8_t wheel_position_sensor_R;				/*!< position sensor data of right motor */
   uint8_t wheel_position_sensor_L;				/*!< position sensor data of left motor */

   float travelled_distance;					/*!< Travelled distance data */
   float car_speed;

   uint8_t steering_stop_sensor_R;				/*!< Steering position data */
   uint8_t steering_stop_sensor_L;				/*!< Steering position data */

   uint16_t motor_current_R;	         			/*!< Right motor current data */
   uint16_t motor_current_L;	         			/*!<  Left motor current data */

   uint8_t errors_SPI;							/*!< Errors of communication data */
} data_STM_t;


/**
 * @brief data updated by the Raspberry Pi
 * size: 4 bytes
 */
typedef struct {
  uint8_t motor_prop;							/*!< Propulsion motors data */
  uint8_t motor_dir;							/*!< Direction motor data */
  uint8_t led;									/*!< LED data */

  uint8_t errors_SPI;							/*!< Errors of communication data */
} data_PI_t;

/**
 * @brief STM32 data
 */
extern volatile data_STM_t *pdata_STM;

/**
 * @brief PI data
 */
extern volatile data_PI_t *pdata_PI;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void init_data(void);

#endif // _DATA_INTERFACE_H
