/**
 * @file         dma.h
 * @author     Curtis Team
 * @brief     Headers of functions to handle DMA  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DMA_H
#define _DMA_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void DMA_QuickInit(void);
void DMA_Callback(void);

void DMA_InitBuffer2Periph(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t Periph_DR_Base, uint32_t Memory_DR_Base, uint32_t data_buffer_size);
void DMA_InitPeriph2Buffer(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t Periph_DR_Base, uint32_t Memory_DR_Base, uint32_t data_buffer_size);


#endif // _DMA_H
