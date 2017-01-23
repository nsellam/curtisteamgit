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
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief   Motor used for example.
*/
#define MOTOR               REAR_MOTOR_R

/**
 * @brief   Duration time of each step. 
*/
#define WAIT_TIME           10000 //ms

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Current_display(void);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Lauches motor and displays the current in it. Motor is initalized, then set to forward 80% during 3 seconds, 
                                                                then stoped during 3seconds,
                                                                then set to backward 80% during 3 seconds,
                                                                and finally stoped.
 * @retval  None
*/
void Motor_Diagnoser(void) {   
    System_Time_QuickInit();

    Motor_QuickInit(MOTOR);
   
    Motor_Enable(MOTOR);

    
    Motor_setSpeed(MOTOR, 1.0);
    Current_display();
    
    Motor_setSpeed(MOTOR, 0.0);
    Current_display();
    
    Motor_setSpeed(MOTOR, -1.0);
    Current_display();
    
    Motor_Disable(MOTOR);
    Current_display();

}

/**
 * @brief   Displays the current in the motor during a definied time. 
 * @retval  None
*/
void Current_display(void) {
    int16_t current;
    uint64_t arrivalTime = millis();
    
    while(millis() - arrivalTime < WAIT_TIME) {
        current = Motor_getCurrent(MOTOR);
        printf("%d mA\n", current);
        pause(100);
    }
}

/* Private functions ---------------------------------------------------------*/
