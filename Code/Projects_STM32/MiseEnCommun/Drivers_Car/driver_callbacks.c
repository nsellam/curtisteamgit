/**
 * @file    driver_callbacks.c
 * @author  Curtis Team
 * @brief   Functions to manage callbacks for Drivers_Car layer 
 */
 
/* Includes ------------------------------------------------------------------*/
#include "driver_callbacks.h"
#include "modules_defines.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

__weak void HallSensor_EdgeCallback(uint8_t hall_identifier) {}

void EXTI_Callback(uint32_t EXTI_Line) {
    if (EXTI_Line == HALLSENSOR_L_LINE) HallSensor_EdgeCallback(HALLSENSOR_IDENTIFIER_L);
    if (EXTI_Line == HALLSENSOR_R_LINE) HallSensor_EdgeCallback(HALLSENSOR_IDENTIFIER_R);
}
    
/* Private functions ---------------------------------------------------------*/
