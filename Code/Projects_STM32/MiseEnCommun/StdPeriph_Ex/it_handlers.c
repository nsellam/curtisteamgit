/**
 * @file 		it_handlers.c
 * @author 	Curtis Team
 * @brief 	Main Interrupt Service Routines 
 */

/* Includes ------------------------------------------------------------------*/
#include "it_handlers.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
__INLINE void EXTIx_IRQHandler(uint32_t EXTI_Line);

__weak void EXTI_Callback(uint32_t EXTI_Line) {}
__weak void SysTick_Callback(void) {}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/******************************************************************************/
/**
  * @brief  Handles EXTI0_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void) {
	EXTIx_IRQHandler(EXTI_Line0);
}

/**
  * @brief  Handles EXTI1_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void) {
	EXTIx_IRQHandler(EXTI_Line1);
}

/**
  * @brief  Handles EXTI2_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void) {
	EXTIx_IRQHandler(EXTI_Line2);
}

/**
  * @brief  Handles EXTI3_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void) {
	EXTIx_IRQHandler(EXTI_Line3);
}

/**
  * @brief  Handles EXTI4_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void) {
	EXTIx_IRQHandler(EXTI_Line4);
}

/**
  * @brief  Handles EXTI9_5_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void) {
	EXTIx_IRQHandler(EXTI_Line5);
	EXTIx_IRQHandler(EXTI_Line6);
	EXTIx_IRQHandler(EXTI_Line7);
	EXTIx_IRQHandler(EXTI_Line8);
	EXTIx_IRQHandler(EXTI_Line9);
}

/**
  * @brief  Handles EXTI9_5_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void) {
	EXTIx_IRQHandler(EXTI_Line10);
	EXTIx_IRQHandler(EXTI_Line11);
	EXTIx_IRQHandler(EXTI_Line12);
	EXTIx_IRQHandler(EXTI_Line13);
	EXTIx_IRQHandler(EXTI_Line14);
	EXTIx_IRQHandler(EXTI_Line15);
}

/**
  * @brief  Manage 
  * @param  None
  * @retval None
  */
void EXTIx_IRQHandler(uint32_t EXTI_Line) { 
	if (EXTI_GetFlagStatus(EXTI_Line)) {
		EXTI_Callback(EXTI_Line);
		EXTI_ClearFlag(EXTI_Line);
	}
}

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  Handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void) {}

/**
  * @brief  Handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1) {}
}

/**
  * @brief  Handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1) {}
}

/**
  * @brief  Handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1) {}
}

/**
  * @brief  Handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1) {}
}

/**
  * @brief  Handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void) {}

/**
  * @brief  Handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void) {}

/**
  * @brief  Handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void) {}

/**
  * @brief  Handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void) {
	SysTick_Callback();
}
