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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#define DMA_IRQ_HANDLER(dma, channel) \
   DMA_Callbacks(DMA##dma##_Channel##channel, ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_TE##channel) << 3) + \
                               ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_HT##channel) << 2) + \
                               ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_TC##channel) << 1) + \
                               ((uint8_t)DMA_GetFlagStatus(DMA##dma##_FLAG_GL##channel) << 0)); \
   DMA_ClearITPendingBit(DMA##dma##_IT_GL##channel);

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void DMA_Callbacks(DMA_Channel_TypeDef * channel, uint8_t flags);

/* Private functions ---------------------------------------------------------*/



/********************************/
/*       Public Functions       */
/********************************/


/**
 * @brief  Callback for the DMA interrupts for SPIComm.
 * @param  dma     DMA number
 * @param  channel Channel number
 * @param  flags   Interrupts flags
 * @retval None
 */
__weak void SPIComm_DMA_callback(DMA_Channel_TypeDef * channel, uint8_t flags){}

   

/********************************/
/*      Private Functions       */
/********************************/


/******************************************************************************/
/*                         IT Callbacks                                       */
/******************************************************************************/

void DMA_Callbacks(DMA_Channel_TypeDef * channel, uint8_t flags) {
   SPIComm_DMA_callback(channel, flags);
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
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
