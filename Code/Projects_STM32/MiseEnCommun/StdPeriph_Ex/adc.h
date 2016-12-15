/**
 * @file	adc.h
 * @author	Curtis Team
 * @brief	Headers of functions to handle ADCs  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ADC_H
#define _ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_QuickInit(ADC_TypeDef* ADCx, uint8_t channelx, uint8_t SampleTime, uint8_t Rank);
void ADC_Callback(void);

#endif // _ADC_H
