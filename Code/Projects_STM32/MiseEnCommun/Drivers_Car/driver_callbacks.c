/**
 * @file    driver_callbacks.c
 * @author  Curtis Team
 * @brief   Functions to manage callbacks for Drivers_Car layer 
 */
 
/* Includes ------------------------------------------------------------------*/
#include "driver_callbacks.h"
#include "common_constants.h"
#include "modules_definitions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

__weak void HallSensor_EdgeCallback(HallSensors_Enum hall_identifier) {}
__weak void FrontMotor_Callback(side_TypeDef direction) {}
    
void EXTI_Callback(uint32_t EXTI_Line) {
    if (EXTI_Line == HALLSENSOR_L_LINE) HallSensor_EdgeCallback(HALLSENSOR_L);
    if (EXTI_Line == HALLSENSOR_R_LINE) HallSensor_EdgeCallback(HALLSENSOR_R);
    if (EXTI_Line == FRONT_LINE_LEFT)   FrontMotor_Callback(LEFT);
    if (EXTI_Line == FRONT_LINE_RIGHT)  FrontMotor_Callback(RIGHT);
}
    
/* Private functions ---------------------------------------------------------*/
