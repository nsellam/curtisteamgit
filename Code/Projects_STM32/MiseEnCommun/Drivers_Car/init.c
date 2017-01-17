/**
 * @file    init.c
 * @author  Curtis Team
 * @brief   To initialize everything
 */
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#include "init.h"

#include "hall_sensors.h"
#include "motors.h"
#include "spi_comm.h"
#include "system_time.h"
#include "position_sensors.h"
#include "speed_sensors.h"
#include "front_motor.h"
#include "rear_motors.h"
#include "mirroring.h"
#include "data_interface.h"

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Public functions ----------------------------------------------------------*/


/** 
* @brief  Initializes all the sensors / actuators in the same time
* @retval none  
*/

void Init (void) {
    
    init_data();
    
    System_Time_QuickInit();
    
    HallSensor_QuickInit(HALLSENSOR_L);
    HallSensor_QuickInit(HALLSENSOR_R);
    
    Motor_QuickInit(REAR_MOTOR_L);
    Motor_QuickInit(REAR_MOTOR_R);
    Motor_QuickInit(FRONT_MOTOR);
    
// SPIComm_QuickInit(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size)
    
    PositionSensor_QuickInit(POSITION_SENSOR_L);
    PositionSensor_QuickInit(POSITION_SENSOR_R);
    
    SpeedSensor_QuickInit(SPEED_SENSOR_L);
    SpeedSensor_QuickInit(SPEED_SENSOR_R);
    
    FrontMotor_QuickInit();
    
    RearMotors_QuickInit();
    
    Mirroring_Init();

}

