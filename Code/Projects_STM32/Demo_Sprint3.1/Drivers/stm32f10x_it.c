/**
  ******************************************************************************
  * @file    stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "callbacks_services.h"
#include "systick.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	systick_inc();
        callbacks_services_hall_period();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/






void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler (void);
int exti_clear_flag (uint32_t EXTI_Line);
int exti_callbacks(uint32_t EXTI_Line); 

__weak void callbacks_services_exti(uint32_t EXTI_Line) {}


/**
  * @brief  This function handles EXTI0_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void) {
	exti_callbacks(EXTI_Line0);
}

/**
  * @brief  This function handles EXTI1_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void) {
	exti_callbacks(EXTI_Line1);
}

/**
  * @brief  This function handles EXTI2_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void) {
	exti_callbacks(EXTI_Line2);
}

/**
  * @brief  This function handles EXTI3_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void) {
	exti_callbacks(EXTI_Line3);
}

/**
  * @brief  This function handles EXTI4_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void) {
	exti_callbacks(EXTI_Line4);
}

/**
  * @brief  This function handles EXTI9_5_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void) {
	exti_callbacks(EXTI_Line5);
	exti_callbacks(EXTI_Line6);
	exti_callbacks(EXTI_Line7);
	exti_callbacks(EXTI_Line8);
	exti_callbacks(EXTI_Line9);
}

/**
  * @brief  This function handles EXTI9_5_IRQHandler interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void) {
	exti_callbacks(EXTI_Line10);
	exti_callbacks(EXTI_Line11);
	exti_callbacks(EXTI_Line12);
	exti_callbacks(EXTI_Line13);
	exti_callbacks(EXTI_Line14);
	exti_callbacks(EXTI_Line15);
}

// TODO : revoir codes d'erreur
int exti_callbacks(uint32_t EXTI_Line) {
	int R = -1; 
	if (EXTI_GetFlagStatus(EXTI_Line)) {
		callbacks_services_exti(EXTI_Line);
		EXTI_ClearFlag(EXTI_Line);
		R = 1; 
	} 
	return R;
}





/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#define DMA_IRQ_HANDLER(dma, channel) \
   DMA_Callbacks(dma, channel, ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_TE##channel) << 3) +\
                               ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_HT##channel) << 2) +\
                               ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_TC##channel) << 1) +\
                               ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_GL##channel) << 0));\
   DMA_ClearITPendingBit(DMA##dma##_IT_GL##channel);

/* Private variables ---------------------------------------------------------*/

const DMA_Channel_TypeDef * GET_DMA_CHANNEL[2][8] = {
   {0            , DMA1_Channel1, DMA1_Channel2, DMA1_Channel3, DMA1_Channel4, DMA1_Channel5, DMA1_Channel6, DMA1_Channel7},
   {0            , DMA2_Channel1, DMA2_Channel2, DMA2_Channel3, DMA2_Channel4, DMA2_Channel5, 0            , 0            }
};

/* Private function prototypes -----------------------------------------------*/

void DMA_Callbacks(int dma, int channel, uint8_t flags);

/* Private functions ---------------------------------------------------------*/



/********************************/
/*       Public Functions       */
/********************************/


/**
 * @brief  Handles the DMA interrupts for SPIComm.
 * @param  dma     DMA number
 * @param  channel Channel number
 * @param  flags   Interrupts flags
 * @retval None
 */
__weak void SPIComm_DMA_Callback(int dma, int channel, uint8_t flags){}

   

/********************************/
/*      Private Functions       */
/********************************/


/******************************************************************************/
/*                         IT Callbacks                                       */
/******************************************************************************/

void DMA_Callbacks(int dma, int channel, uint8_t flags) {
   SPIComm_DMA_Callback(dma, channel, flags);
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles DMA1_Channel1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 1)
}

/**
  * @brief  This function handles DMA1_Channel2 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel2_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 2)
}

/**
  * @brief  This function handles DMA1_Channel3 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel3_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 3)
}

/**
  * @brief  This function handles DMA1_Channel4 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel4_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 4)
}

/**
  * @brief  This function handles DMA1_Channel5 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel5_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 5)
}

/**
  * @brief  This function handles DMA1_Channel6 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel6_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 6)
}

/**
  * @brief  This function handles DMA1_Channel7 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 7)
   
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
