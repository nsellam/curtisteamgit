/**
 * @file    it_handlers.h
 * @author  Curtis Team
 * @brief   Header of Main Interrupt Service Routines
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _IT_HANDLERS_H
#define _IT_HANDLERS_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void EXTI_ITHandler(uint32_t EXTI_Line);
void DMA_ITHandler(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t flags);
void ADC_ITHandler(ADC_TypeDef* ADCx, uint8_t flags);
void TIM_ITHandler(TIM_TypeDef* TIMx);
void SPI_ITHandler(SPI_TypeDef* SPIx);
void SysTick_ITHandler(void);

#endif // _IT_HANDLERS_H
