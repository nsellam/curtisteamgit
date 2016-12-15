/**
 * @file    nvic.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle NVIC  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _NVIC_H
#define _NVIC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void NVIC_QuickInit(int8_t IRQChannel, uint8_t priority);

#endif // _NVIC_H
