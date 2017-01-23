/**
 * @file    data_interface.c
 * @author  Curtis Team
 * @brief   Functions for initialization of sensors and actuators
 */
 
/********************************/
/*       LIBRARIES              */
/********************************/
#include <data_interface.h>
#include <pthread.h>

/********************************/
/*       DEFINES                */
/********************************/
/**
* @brief    Value for 8 bits variables
*/
#define INITIAL_8B_VALUE      ((int8_t)(0x00))

/**
* @brief    Value for 16 bits variables
*/
#define INITIAL_16B_VALUE     ((int16_t)(0x0000))

/**
* @brief    Value for float variables
*/
#define INITIAL_FLOAT_VALUE   ((float)(0.0))


/********************************/
/*       VARIABLES                */
/********************************/

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
/**
 * @brief   m_data_PI mutex for PI data
 */
pthread_mutex_t m_data_PI;
/**
 * @brief   m_data_STM mutex for STM data
 */
pthread_mutex_t m_data_STM;

/**
 * @ send_error
 * @brief to store the errors when SPI sending 
 */
int send_error = 0x00;

/**
 * @ canary_error_count
 * @brief to count the canary errors 
 */
int canary_error_count = 0x00;

/**
 * @ crc_error_count
 * @brief to count the crc errors 
 */
int crc_error_count = 0x00;

int mirroring_cycles_count = 0;

/********************************/
/*       PROTOTYPES              */
/********************************/

void init_data_PI(void);
void init_data_STM(void);

/********************************/
/*       FUNCTIONS              */
/********************************/

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
   data_STM.ultrasonic_sensors[i]   = INITIAL_8B_VALUE;
   data_STM.wheel_position_sensor_R = INITIAL_8B_VALUE;
   data_STM.wheel_position_sensor_L = INITIAL_8B_VALUE;
   float travelled_distance_R       = INITIAL_FLOAT_VALUE;					
   float travelled_distance_L       = INITIAL_FLOAT_VALUE;					
   float wheel_speed_R              = INITIAL_FLOAT_VALUE;						
   float wheel_speed_L              = INITIAL_FLOAT_VALUE;						
   data_STM.steering_stop_sensor_R  = INITIAL_8B_VALUE;
   data_STM.steering_stop_sensor_L  = INITIAL_8B_VALUE;
   data_STM.motor_current_R         = INITIAL_16B_VALUE;
   data_STM.motor_current_L         = INITIAL_16B_VALUE;
   data_STM.battery_level             = INITIAL_8B_VALUE;
   data_STM.errors_SPI              = INITIAL_8B_VALUE;
}

/**
 * @brief   Initializes the data_PI structure with bytes of zeros
 * @retval  None
 */
void init_data_PI(void) {
   data_PI.motor_prop = INITIAL_8B_VALUE;
   data_PI.motor_dir  = NONE;
   data_PI.enable_motors_control = INITIAL_8B_VALUE;
   data_PI.errors_SPI = INITIAL_8B_VALUE;
}
