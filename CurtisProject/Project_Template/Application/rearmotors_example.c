/**
 * @file    rearmotors_example.c
 * @author  Curtis Team
 * @brief   Rear motors API use case example
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "rear_motors.h"
#include "system_time.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Tests rear motor by setting a speed. Expected behavior is a regulated speed. 
 * @retval  None
*/
void RearMotors_Example(void) {
    RearMotors_QuickInit();
    System_Time_QuickInit();
    RearMotors_Enable();
    RearMotors_setSpeed(10);
    while(1) {}
}

/* Private functions ---------------------------------------------------------*/
