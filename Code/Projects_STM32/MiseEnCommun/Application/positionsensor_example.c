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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Measures car position. 
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void PositionSensor_Example(PositionSensor_Enum PositionSensor_identifier) {
    volatile float WheelPosition = 0; 
    
    System_Time_QuickInit();
    PositionSensor_QuickInit(PositionSensor_identifier); 
    
    while(1) {
        pause(100); 
        WheelPosition = PositionSensor_get(POSITION_M, PositionSensor_identifier);
    }
    
}

/* Private functions ---------------------------------------------------------*/
