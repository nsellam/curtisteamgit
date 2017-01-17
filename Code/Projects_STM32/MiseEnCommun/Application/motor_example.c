/**
 * @file    motor_example.c
 * @author  Curtis Team
 * @brief   Motors API use case example 
 * (system_time.h API is not required to use motors.h : it is used here to have a more visual demonstration)
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "system_time.h"
#include "motors.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Lauches motors. Motor are initalized, then set to forward 80% during 3 seconds, 
                                                then stoped during 3seconds,
                                                then set to backward 80% during 3 seconds,
                                                and finally stoped.
 * @retval  None
*/
void Motor_Example(void) {
    System_Time_QuickInit();

    Motor_QuickInit(REAR_MOTOR_L);
    Motor_QuickInit(REAR_MOTOR_R);
   
    Motor_Enable(REAR_MOTOR_L);
    Motor_Enable(REAR_MOTOR_R);
    
    Motor_setSpeed(REAR_MOTOR_L, 1.0);
    Motor_setSpeed(REAR_MOTOR_R, 1.0);
    pause(1000*3);
    Motor_setSpeed(REAR_MOTOR_L, 0.0);
    Motor_setSpeed(REAR_MOTOR_R, 0.0);
    pause(1000*3);
    Motor_setSpeed(REAR_MOTOR_L, -1.0);
    Motor_setSpeed(REAR_MOTOR_R, -1.0);
    pause(1000*3);
    
    Motor_Disable(REAR_MOTOR_L);
    Motor_Disable(REAR_MOTOR_R);
}

/* Private functions ---------------------------------------------------------*/
