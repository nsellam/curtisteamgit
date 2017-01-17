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
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Measures car speed. 
 * @retval  None
*/
void SpeedSensor_Example(void) {
    float WheelSpeed_L = 0; 
    float WheelSpeed_R = 0; 
    
    System_Time_QuickInit();
    PositionSensor_QuickInit(SPEED_SENSOR_L); 
    PositionSensor_QuickInit(SPEED_SENSOR_R); 
    
    while(1) {
        pause(100); 
        WheelSpeed_L = SpeedSensor_get(SPEED_M_S, SPEED_SENSOR_L);
        WheelSpeed_R = SpeedSensor_get(SPEED_M_S, SPEED_SENSOR_R);
        printf("Left  wheel: %.2f \n", WheelSpeed_L);
        printf("Right wheel: %.2f \n", WheelSpeed_R);
    }
}

/* Private functions ---------------------------------------------------------*/
