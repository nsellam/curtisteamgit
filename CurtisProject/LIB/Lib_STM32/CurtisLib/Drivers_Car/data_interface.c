/**
 * @file    data_interface.c
 * @author  Curtis Team
 * @brief   Functions for initialization of sensors and actuators
 */
 
/* Includes ------------------------------------------------------------------*/
#include "data_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
* @brief    Value for 8 bits variables
*/
#define INITIAL_8B_VALUE      ((int8_t)0x00)

/**
* @brief    Value for 16 bits variables
*/
#define INITIAL_16B_VALUE     ((int16_t)0x0000)

/**
* @brief    Value for float variables
*/
#define INITIAL_FLOAT_VALUE   ((float)0.0)

/**
* @brief    Value for motors variables
*/
#define INITIAL_MOTOR_VALUE   127
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/**
 * @brief   STM32 data
 */
volatile data_STM_t data_STM;
/**
 * @brief STM32 data
 */
volatile data_STM_t *pdata_STM = &data_STM;
/**
 * @brief   PI data
 */
volatile data_PI_t data_PI;
/**
 * @brief   PI data
 */
volatile data_PI_t *pdata_PI = &data_PI;
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void init_data_PI(void);
void init_data_STM(void);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Initializes the data_PI and data_STM structures
 * @retval  None
 */
void init_data(void) {
   init_data_PI();
   init_data_STM();
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Initializes the data_STM structure with bytes of zeros
 * @retval  None
 */
void init_data_STM(void) {
   int i;

   for(i = 0; i < DATA_STM_US_NUM; i++)
      data_STM.ultrasonic_sensors[i] = INITIAL_8B_VALUE;

   data_STM.wheel_position_sensor_R = INITIAL_8B_VALUE;
   data_STM.wheel_position_sensor_L = INITIAL_8B_VALUE;
   data_STM.steering_stop_sensor_R  = INITIAL_8B_VALUE;
   data_STM.steering_stop_sensor_L  = INITIAL_8B_VALUE;
   data_STM.motor_current_R         = INITIAL_16B_VALUE;
   data_STM.motor_current_L         = INITIAL_16B_VALUE;
   data_STM.errors_SPI              = INITIAL_8B_VALUE;

	data_STM.car_speed					= INITIAL_MOTOR_VALUE;
	data_STM.travelled_distance		= INITIAL_FLOAT_VALUE;
}

/**
 * @brief   Initializes the data_PI structure with bytes of zeros
 * @retval  None
 */
void init_data_PI(void) {
   data_PI.motor_prop = INITIAL_8B_VALUE;
   data_PI.motor_dir  = INITIAL_8B_VALUE;
   data_PI.led        = INITIAL_8B_VALUE;
   data_PI.errors_SPI = INITIAL_8B_VALUE;
}
