/**
 * @file    speed_sensors.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle speed sensors   
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPEED_SENSOR_H
#define _SPEED_SENSOR_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"
#include "modules_definitions.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @brief   Left position sensor identifier
*/
#define SPEED_SENSOR_L              HALLSENSOR_L          

/**
 * @brief   Right position sensor identifier
*/
#define SPEED_SENSOR_R              HALLSENSOR_R          

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SpeedSensor_QuickInit(SpeedSensor_Enum SpeedSensor_identifier);
float SpeedSensor_get(float unit, SpeedSensor_Enum SpeedSensor_identifier);

#endif // _SPEED_SENSOR_H
