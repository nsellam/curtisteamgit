/**
 * @file    driver_callbacks.h
 * @author  Curtis Team
 * @brief   Headers of functions to manage callbacks for Drivers_Car layer 
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DRIVER_CALLBACKS_H
#define _DRIVER_CALLBACKS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void EXTI_Callback(uint32_t EXTI_Line);

void DMA_Callback(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t flags);

void TIM_Callback(TIM_TypeDef TIMx);

#endif // _DRIVER_CALLBACKS_H
