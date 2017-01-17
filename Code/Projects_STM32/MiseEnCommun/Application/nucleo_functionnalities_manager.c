/**
 * @file    nucleo_functionnalities_manager.c
 * @author  Curtis Team
 * @brief   for the updates of the data structures and of the car commands
 */


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>

#include "data_interface.h" 
#include "rear_motors.h"
#include "front_motor.h"
#include "motors.h"
#include "speed_sensors.h"
#include "position_sensors.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define MANAGER_TIME_BETWEEN_TWO_UPDATES 1

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/



/* Private variables ---------------------------------------------------------*/
float motor_speed = 0.0;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/




/**
 * @brief   Counter to determine command refreshing time
*/
uint32_t Manager_remainingTimeInCommandPeriod = MANAGER_TIME_BETWEEN_TWO_UPDATES;


/**
 * @brief   Callback associated to the nucleo functionnalities manager whose aim is to set the adequate command and update the sensors' data
 * @retval	None
*/
void Manager_Callback(void) {
    Manager_remainingTimeInCommandPeriod --;
    
    if (Manager_remainingTimeInCommandPeriod == 0) {
    // ACTUATORS    
        // Rear motors
        if (pdata_PI->enable_motors_control == ENABLE) {
          speed_cmd = pdata_PI->motor_prop;  
          RearMotor_controlL(speed_cmd);
        }
        else if (pdata_PI->enable_motors_control != ENABLE) {
            motor_speed = (float)(pdata_PI->motor_prop);
            Motor_setSpeed(REAR_MOTOR_L, motor_speed);
            Motor_setSpeed(REAR_MOTOR_R, motor_speed);
        }
    
        // Front motors
        if (pdata_PI->motor_dir == LEFT || pdata_PI->motor_dir == RIGHT){
          FrontMotor_turn (pdata_PI->motor_dir);
        }
        else if (pdata_PI->motor_dir != LEFT && pdata_PI->motor_dir != RIGHT) {
            ;// do nothing
        }
        
    // SENSORS   
        // wheel speed    
        pdata_STM->wheel_speed_R = SpeedSensor_get(SPEED_CM_S, SPEED_SENSOR_R);
        pdata_STM->wheel_speed_L = SpeedSensor_get(SPEED_CM_S, SPEED_SENSOR_L);
        
        // travelled distance
        pdata_STM->travelled_distance_R = PositionSensor_get(POSITION_CM, POSITION_SENSOR_R);
        pdata_STM->travelled_distance_L = PositionSensor_get(POSITION_CM, POSITION_SENSOR_L);
        
        
        //motors current
       // pdata_STM->motor_current_R = ;
       // pdata_STM->motor_current_L = ;
        Manager_remainingTimeInCommandPeriod = MANAGER_TIME_BETWEEN_TWO_UPDATES;


            
    }
}
