#include <stdint.h>
#include <stm32f10x.h>

#include "common_constants.h"
#include "system_time.h"
#include "position_sensors.h"

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
