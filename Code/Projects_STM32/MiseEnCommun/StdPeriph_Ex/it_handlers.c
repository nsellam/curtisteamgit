/**
 * @file 	it_handlers.c
 * @author 	Curtis Team
 * @brief 	Main Interrupt Service Routines 
*/

/* Includes ------------------------------------------------------------------*/
#include "it_handlers.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define DMA_IRQ_HANDLER(dma, channel) \
   DMA_ITHandler(DMA##dma##_Channel##channel,   ((uint8_t)DMA_GetITStatus(DMA##dma##_FLAG_TE##channel) << 3) +\
                                                ((uint8_t)DMA_GetITStatus(DMA##dma##_FLAG_HT##channel) << 2) +\
                                                ((uint8_t)DMA_GetITStatus(DMA##dma##_FLAG_TC##channel) << 1) +\
                                                ((uint8_t)DMA_GetITStatus(DMA##dma##_FLAG_GL##channel) << 0));\
   DMA_ClearITPendingBit(DMA##dma##_IT_GL##channel);

#define ADC_IRQ_HANDLER(adc) \
   flags =  ((uint8_t) ADC_GetITStatus(ADC##adc, ADC_FLAG_AWD)   << 4) + \
            ((uint8_t) ADC_GetITStatus(ADC##adc, ADC_FLAG_EOC)   << 3) + \
            ((uint8_t) ADC_GetITStatus(ADC##adc, ADC_FLAG_JEOC)  << 2) + \
            ((uint8_t) ADC_GetITStatus(ADC##adc, ADC_FLAG_JSTRT) << 1) + \
            ((uint8_t) ADC_GetITStatus(ADC##adc, ADC_FLAG_STRT)  << 0); \
   if (flags != 0) { \
       ADC_ITHandler(*ADC##adc, flags); \
       ADC_ClearITPendingBit(ADC##adc, ADC_FLAG_AWD); \
       ADC_ClearITPendingBit(ADC##adc, ADC_FLAG_EOC); \
       ADC_ClearITPendingBit(ADC##adc, ADC_FLAG_JEOC); \
   } \


/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
__INLINE void EXTIx_IRQHandler(uint32_t EXTI_Line);

__weak void EXTI_ITHandler(uint32_t EXTI_Line) {}

__weak void SysTick_Callback(void) {}
    
__weak void DMA_ITHandler(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t flags) {}
    
__weak void ADC_ITHandler(ADC_TypeDef ADCx, uint8_t flags) {}
    
__weak void TIM_ITHandler(TIM_TypeDef TIMx) {}
    
__weak void SPI_ITHandler(SPI_TypeDef SPIx) {}

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
 * @brief  Manages externa interrupts 
 * @param  None
 * @retval None
*/
void EXTIx_IRQHandler(uint32_t EXTI_Line) { 
	if (EXTI_GetFlagStatus(EXTI_Line)) {
		EXTI_ITHandler(EXTI_Line);
		EXTI_ClearFlag(EXTI_Line);
	}
}

void ADC1_2_IRQHandler (void) {
    uint8_t flags = 0; 
    ADC_IRQ_HANDLER(1)
    ADC_IRQ_HANDLER(2)
}


/**
 * @brief  Handles DMA1_Channel1 interrupt request.
 * @param  None
 * @retval None
*/
void DMA1_Channel1_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 1)
}

/**
 * @brief  Handles DMA1_Channel2 interrupt request.
 * @param  None
 * @retval None
*/
void DMA1_Channel2_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 2)
}

/**
 * @brief  Handles DMA1_Channel3 interrupt request.
 * @param  None
 * @retval None
*/
void DMA1_Channel3_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 3)
}

/**
 * @brief  Handles DMA1_Channel4 interrupt request.
 * @param  None
 * @retval None
*/
void DMA1_Channel4_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 4)
}

/**
 * @brief  Handles DMA1_Channel5 interrupt request.
 * @param  None
 * @retval None
*/
void DMA1_Channel5_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 5)
}

/**
 * @brief  Handles DMA1_Channel6 interrupt request.
 * @param  None
 * @retval None
*/
void DMA1_Channel6_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 6)
}

/**
 * @brief  Handles DMA1_Channel7 interrupt request.
 * @param  None
 * @retval None
*/
void DMA1_Channel7_IRQHandler(void) {
   DMA_IRQ_HANDLER(1, 7)
}

/**
 * @brief  Handles TIM1 up interrupt request.
 * @param  None
 * @retval None
*/
void TIM1_UP_IRQHandler(void) {
    TIM_ITHandler(*TIM1);
}

/**
 * @brief  Handles TIM2 interrupt request.
 * @param  None
 * @retval None
*/
void TIM2_IRQHandler(void) {
    TIM_ITHandler(*TIM2);
}

/**
 * @brief  Handles TIM3 interrupt request.
 * @param  None
 * @retval None
*/
void TIM3_IRQHandler(void) {
    TIM_ITHandler(*TIM3);
}

/**
 * @brief  Handles TIM4 interrupt request.
 * @param  None
 * @retval None
*/
void TIM4_IRQHandler(void) {
    TIM_ITHandler(*TIM4);
}

/**
 * @brief  Handles SPI1 interrupt request.
 * @param  None
 * @retval None
*/
void SPI1_IRQHandler(void) {
    SPI_ITHandler(*SPI1);
}

/**
 * @brief  Handles SPI2 interrupt request.
 * @param  None
 * @retval None
*/
void SPI2_IRQHandler(void) {
    SPI_ITHandler(*SPI2);
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
