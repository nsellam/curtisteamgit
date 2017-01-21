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
void ADC_Diagnoser(void);              
void GPIO_Diagnoser(void);             
void Motor_Diagnoser(void);
void PWM_Diagnoser(void);              
void Battery_Diagnoser(void); 
void HallSensor_Diagnoser(void);      

#endif // _EXAMPLES_H
