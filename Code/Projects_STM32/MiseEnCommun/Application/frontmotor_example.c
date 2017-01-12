#include <stdint.h>
#include <stm32f10x.h>

#include "system_time.h"
#include "front_motor.h"

/**
 * @brief   Tests front motor by turning left, expecting 1 second and turning right. 
 * @retval  None
*/
void FrontMotor_Example(void) {
    System_Time_QuickInit();
    FrontMotor_QuickInit();
    while(1) {
        FrontMotor_turn(LEFT); 
        pause(3000);
        FrontMotor_turn(RIGHT);
        pause(3000);
    }
}
