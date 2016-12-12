/**
 * @file 		spi.h
 * @author 	Curtis Team
 * @brief 	Headers of functions to handle SPI
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPI_H
#define _SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SPI_QuickInit(void);
void SPI_Callback(void);

#endif // _SPI_H
