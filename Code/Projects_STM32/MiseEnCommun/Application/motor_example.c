#include <stdint.h>
#include <stm32f10x.h>

#include "system_time.h"
#include "motors.h"

/**
 * @brief   Lauches motor. Motor is initalized, then set to forward 80% during 3 seconds, 
                                                then stoped during 3seconds,
                                                then set to backward 80% during 3 seconds,
                                                and finally stoped.
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void Motor_Example(Motors_Enum Motor) {
    System_Time_QuickInit();
    Motor_QuickInit(Motor);
    Motor_Enable(Motor);
    
    Motor_setSpeed(Motor, 1.0);
    pause(1000*3);
    Motor_setSpeed(Motor, 0.0);
    pause(1000*3);
    Motor_setSpeed(Motor, -1.0);
    pause(1000*3);
    
    Motor_Disable(Motor);
}