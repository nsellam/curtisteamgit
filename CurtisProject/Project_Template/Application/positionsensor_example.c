/**
 * @file    positionsensor_example.c
 * @author  Curtis Team
 * @brief   Position sensors API use case example
 * (system_time.h API is not required to use position_sensors.h : it is used here to have a more visual demonstration)
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "common_constants.h"
#include "system_time.h"
#include "position_sensors.h"
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Measures car position. 
 * @retval  None
*/
void PositionSensor_Example(void) {
    float WheelPosition_L = 0; 
    float WheelPosition_R = 0; 
    
    System_Time_QuickInit();
    PositionSensor_QuickInit(SENSOR_L); 
    PositionSensor_QuickInit(SENSOR_L); 
    
    while(1) {
        pause(100); 
        WheelPosition_L = PositionSensor_get(POSITION_CM, SENSOR_L);
        WheelPosition_R = PositionSensor_get(POSITION_CM, SENSOR_R);
        printf("Left  wheel: %.2f cm \n", WheelPosition_L);
        printf("Right wheel: %.2f cm \n", WheelPosition_R);
    }
}

/* Private functions ---------------------------------------------------------*/
