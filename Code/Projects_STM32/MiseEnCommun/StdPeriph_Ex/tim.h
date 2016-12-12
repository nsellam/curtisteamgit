/**
 * @file 		tim.h
 * @author 	Curtis Team
 * @brief 	Headers of functions to handle Timers  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TIM_H
#define _TIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
* @brief Number of microseconds per second
*/
#define US_PER_S  (1.0e+06)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
float TIM_QuickInit(TIM_TypeDef *Timer, float period_us);
void TIM_Callback(void);
void TIM_Enable(TIM_TypeDef *Timer);

#endif // _TIM_H
