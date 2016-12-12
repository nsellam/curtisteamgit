/**
 * @file 		dma.h
 * @author 	Curtis Team
 * @brief 	Headers of functions to handle DMA  
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

void DMA_InitBuffer2Periph(void);
void DMA_Periph2InitBuffer(void);


#endif // _DMA_H
