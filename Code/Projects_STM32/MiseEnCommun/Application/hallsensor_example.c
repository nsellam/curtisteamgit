/**
 * @file    hallsensor_example.c
 * @author  Curtis Team
 * @brief   Hall sensors API use case example
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "hall_sensors.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Lauches hall sensor. After this procedure, hall-sensor interrupts detected. Best way to see it is to run debug mode and insert a breakpoint in the function HallSensor_EdgeCallback().
 * @param   hall_identifier Hall Sensor to be considered
 * @retval  None
*/
void HallSensor_Example(HallSensors_Enum hall_identifier) {
    HallSensor_QuickInit(hall_identifier);
}

/* Private functions ---------------------------------------------------------*/
