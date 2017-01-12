/**
 * @file    speedsensor_example.c
 * @author  Curtis Team
 * @brief   Speed sensors API use case example
 * (system_time.h API is not required to use speed_sensors.h : it is used here to have a more visual demonstration)
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "common_constants.h"
#include "system_time.h"
#include "position_sensors.h"
#include "speed_sensors.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Measures car speed. 
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void SpeedSensor_Example(SpeedSensor_Enum SpeedSensor_identifier) {
    float WheelSpeed = 0; 
    
    System_Time_QuickInit();
    PositionSensor_QuickInit(SpeedSensor_identifier); 
    
    while(WheelSpeed >= 0) {
        pause(100); 
        WheelSpeed = SpeedSensor_get(SPEED_M_S, SpeedSensor_identifier);
    }
}

/* Private functions ---------------------------------------------------------*/
