#include <stdint.h>
#include <stm32f10x.h>

#include "common_constants.h"
#include "system_time.h"
#include "position_sensors.h"
#include "speed_sensors.h"

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
