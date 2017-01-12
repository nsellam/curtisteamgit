/**
 * @file    examples.h
 * @author  Curtis Team
 * @brief   Headers of API use case examples
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _EXAMPLES_H
#define _EXAMPLES_H
 
/* Includes ------------------------------------------------------------------*/
#include "modules_definitions.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_Example(void);
void PWM_Example(void);
void GPIO_Example(void);
void HallSensor_Example(HallSensors_Enum hall_identifier);
void Motor_Example(Motors_Enum Motor);
void PositionSensor_Example(PositionSensor_Enum PositionSensor_identifier);
void SpeedSensor_Example(SpeedSensor_Enum SpeedSensor_identifier);
void FrontMotor_Example(void);
void RearMotors_Example(void);

#endif // _EXAMPLES_H
