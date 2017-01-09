/**
 * @file    dma.c
 * @author  Curtis Team
 * @brief   Functions to handle DMA
 */

/* Includes ------------------------------------------------------------------*/
#include "dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void DMA_ClockEnable(DMA_Channel_TypeDef* DMAy_Channelx);

/* Public functions ----------------------------------------------------------*/

/**
 * @brief   Makes the initialization of the given Direct Memory Access (DMA) with the parameters specified
 * @param   DMAy_Channelx DMA_Channel_TypeDef* Number of the DMA and of the channel used
 * @param   Periph_DR_Base uint32_t Base adress of the peripheral
 * @param   Memory_DR_Base uint32_t Base adress of the memory to use
 * @param   data_buffer_size uint32_t size of the buffer
*/
void DMA_InitPeriph2Buffer(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t PeripheralBaseAddr, uint32_t MemoryBaseAddr, uint32_t MemoryBufferSize) {

    DMA_InitTypeDef DMA_InitStructure;

    DMA_InitStructure.DMA_DIR                   = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_Priority              = DMA_Priority_VeryHigh;
    
    DMA_InitStructure.DMA_PeripheralBaseAddr    = PeripheralBaseAddr;
    DMA_InitStructure.DMA_MemoryBaseAddr        = MemoryBaseAddr;
    DMA_InitStructure.DMA_BufferSize            = MemoryBufferSize;
    
    DMA_InitStructure.DMA_PeripheralInc         = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc             = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize    = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize        = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode                  = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M                   = DMA_M2M_Disable;

    DMA_Init(DMAy_Channelx, &DMA_InitStructure);

}

/**
 * @brief   Makes the initialization of the given Direct Memory Access (DMA) with the parameters specified
 * @param   DMAy_Channelx DMA_Channel_TypeDef* Number of the DMA and of the channel used
 * @param   Periph_DR_Base uint32_t Base adress of the peripheral
 * @param   Memory_DR_Base uint32_t Base adress of the memory to use
 * @param   data_buffer_size uint32_t size of the buffer
*/
void DMA_InitBuffer2Periph(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t PeripheralBaseAddr, uint32_t MemoryBaseAddr, uint32_t MemoryBufferSize) {
    
    DMA_InitTypeDef DMA_InitStructure;

    DMA_InitStructure.DMA_DIR                   = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_Priority              = DMA_Priority_VeryHigh;
    
    DMA_InitStructure.DMA_PeripheralBaseAddr    = PeripheralBaseAddr;
    DMA_InitStructure.DMA_MemoryBaseAddr        = MemoryBaseAddr;
    DMA_InitStructure.DMA_BufferSize            = MemoryBufferSize;
    
    DMA_InitStructure.DMA_PeripheralInc         = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc             = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize    = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize        = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode                  = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M                   = DMA_M2M_Disable;
    
    DMA_Init(DMAy_Channelx, &DMA_InitStructure);
    
}

__weak void DMA_Callback(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t flags) {}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Enables clock on the adequate DMA
 * @param   DMAy_Channelx DMA_Channel_TypeDef* (DMA to switch on the clock)
 * @retval  None
*/
void DMA_ClockEnable(DMA_Channel_TypeDef* DMAy_Channelx) {
    if (            (DMAy_Channelx == DMA1_Channel1) || 
                        (DMAy_Channelx == DMA1_Channel2) || 
                        (DMAy_Channelx == DMA1_Channel3) || 
                        (DMAy_Channelx == DMA1_Channel4) || 
                        (DMAy_Channelx == DMA1_Channel5) || 
                        (DMAy_Channelx == DMA1_Channel6) || 
                        (DMAy_Channelx == DMA1_Channel7)) {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    }
    else if (    (DMAy_Channelx == DMA2_Channel1) || 
                        (DMAy_Channelx == DMA2_Channel2) || 
                        (DMAy_Channelx == DMA2_Channel3) || 
                        (DMAy_Channelx == DMA2_Channel4) || 
                        (DMAy_Channelx == DMA2_Channel5)) {
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
    }
}

/**
 * @brief   Handler associated to DMA
*/
void DMA_ITHandler(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t flags) {
    DMA_Callback(DMAy_Channelx, flags);
}
