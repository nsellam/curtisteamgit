/**
 * @file 		nvic.c
 * @author 	Curtis Team
 * @brief 	Functions to handle NVIC  
 */
 
 /* Includes ------------------------------------------------------------------*/
#include "nvic.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief 	Makes the initialization of the given NVIC with the parameters specified
 * @param 	IRQChannel Number of the Interrupt Request to init
 * @param 	priority Priority of the interruption initialized
 * @retval 	None
*/
void NVIC_QuickInit(uint8_t IRQChannel, uint8_t priority) { 
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = IRQChannel; 
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = priority; 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStruct);

}
