#ifndef DATA_H
#define DATA_H

#include <stdint.h>
#include <stddef.h>
//#include <pthread.h>

/************************
 *     DEFINES          *
 ************************/
#define DATA_STM_US_NUM 6

#define DATA_ALIGNMENT_PI  4
#define DATA_SIZE_MAX_RAW  ((sizeof(data_STM_t) > sizeof(data_PI_t)) ? sizeof(data_STM_t) : sizeof(data_PI_t))
#define DATA_SIZE_MAX      (DATA_SIZE_MAX_RAW - (DATA_ALIGNMENT_PI - DATA_SIZE_MAX_RAW % DATA_ALIGNMENT_PI) % DATA_ALIGNMENT_PI)


// Ultrasonic ID

/**
* @raw US_FR : id of front right ultrasonic sensor
*/
#define US_FR 0x00

/**
* @raw US_FM : id of front middle ultrasonic sensor
*/
#define US_FM 0x01

/**
* @raw US_FL : id of front left ultrasonic sensor
*/
#define US_FL 0x02

/**
* @raw US_BR : id of back right ultrasonic sensor
*/
#define US_BR 0x03

/**
* @raw US_BM : id of back middle ultrasonic sensor
*/
#define US_BM 0x04

/**
* @raw US_BL : id of back left ultrasonic sensor
*/
#define US_BL 0x05



// Wheel position sensors 

/**
* @raw WP_R : id of Right wheel position sensor
*/
#define WP_R 0x00

/**
* @raw WP_L : id of Left wheel position sensor
*/
#define WP_L 0x01



// Steering stop sensor

/**
* @raw SS_R : id of Right wheel position sensor
*/
#define SS_R 0x00

/**
* @raw SS_L : id of Left wheel position sensor
*/
#define SS_L 0x01

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

/**
 * @var m_data_PI
 * @brief PI data mutex
 */
//extern pthread_mutex_t m_data_PI;

/**
 * @var m_data_STM
 * @brief STM data mutex
 */
//extern pthread_mutex_t m_data_STM;


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
