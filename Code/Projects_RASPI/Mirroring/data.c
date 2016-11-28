/**
 * @file data.c
 * @author Curtis Team
 * @brief functions for initialization of sensors and actuators
 */


/************************
 *      INCLUDES        *
 ************************/
#include <data.h>

#include <stddef.h>

#define INITIAL_8B_VALUE 0x00
#define INITIAL_16B_VALUE 0x0000
#define INITIAL_32B_VALUE 0x00000000

/************************
 *      VARIABLES       *
 ************************/

volatile data_STM_t data_STM;
volatile data_STM_t *pdata_STM = &data_STM;

volatile data_PI_t data_PI;
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
   data_STM.travelled_distance = 0.0;//INITIAL_32B_VALUE;
   data_STM.car_speed = 0.0;//INITIAL_16B_VALUE;
   data_STM.steering_stop_sensor_R  = INITIAL_8B_VALUE;
   data_STM.steering_stop_sensor_L  = INITIAL_8B_VALUE;
   data_STM.errors_SPI              = INITIAL_8B_VALUE;
}

/**
 * @fn init_data_PI
 * @brief initializes the data_PI structure with bytes of zeros
 * @return void
 */
void init_data_PI(void) {
   data_PI.motor_prop   = INITIAL_8B_VALUE;
   data_PI.motor_dir    = INITIAL_8B_VALUE;
   data_PI.led          = INITIAL_8B_VALUE;
   data_PI.errors_SPI   = INITIAL_8B_VALUE;
}
