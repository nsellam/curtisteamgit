#include <stdint.h>
#include <stm32f10x.h>

#include "rear_motors.h"

/**
 * @brief   Tests rear motor by setting a speed. Expected behavior is a regulated speed. 
 * @retval  None
*/
void RearMotors_Example(void) {
    RearMotors_QuickInit();
    RearMotors_Enable();
    RearMotors_setSpeed(50);
}
