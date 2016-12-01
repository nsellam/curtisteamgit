/**
 * @file spicomm.c
 * @author Curtis Team
 * @brief SPI communication module
 */

/********************************/
/*       LIBRARIES              */
/********************************/
#include "spicomm_st.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <stm32f10x.h>

#include "stm32f10x_it.h"
#include "framecheck.h"

/********************************/
/*       ALIAS                  */
/********************************/

#ifndef SPICOMM_BUFFER_SIZE_MAX
   #define SPICOMM_BUFFER_SIZE_MAX 256
#endif

#define FRAME_CANARY_POS(length) ((length) + 0)
#define FRAME_CRC_POS(length)    (FRAME_CANARY_POS(length) + FRAME_CANARY_SIZE)

#define SPIx                     SPI2
#define SPIx_CLK                 RCC_APB1Periph_SPI2

#define SPIx_GPIO                GPIOB
#define SPIx_GPIO_CLK            RCC_APB2Periph_GPIOB
#define SPIx_PIN_SCK             GPIO_Pin_13
#define SPIx_PIN_MISO            GPIO_Pin_14
#define SPIx_PIN_MOSI            GPIO_Pin_15

#define SPIx_DMA                 DMA1
#define SPIx_DMA_CLK             RCC_AHBPeriph_DMA1
#define SPIx_DMA_Rx_Channel      DMA1_Channel4
#define SPIx_DMA_Tx_Channel      DMA1_Channel5
#define SPIx_DMA_Rx_Channel_IRQn DMA1_Channel4_IRQn
#define SPIx_DMA_Tx_Channel_IRQn DMA1_Channel5_IRQn
#define SPIx_DMA_PRIO            1

#define DMA_FLAGS2STATUS(flags) (((flags) & DMA_FLAG_TE) ? SPICOMM_TRANSFER_ERROR    :\
                                (((flags) & DMA_FLAG_HT) ? SPICOMM_TRANSFER_HALF     :\
                                (((flags) & DMA_FLAG_TC) ? SPICOMM_TRANSFER_COMPLETE : SPICOMM_TRANSFER_UNKNOWN)))

/********************************/
/*       VARIABLES              */
/********************************/

size_t data_buffer_Rx_size;
size_t data_buffer_Tx_size;
uint8_t *data_buffer_Rx;
uint8_t *data_buffer_Tx;

uint8_t frame_buffer_Rx[SPICOMM_BUFFER_SIZE_MAX + FRAME_CHECK_SIZE];
uint8_t frame_buffer_Tx[SPICOMM_BUFFER_SIZE_MAX + FRAME_CHECK_SIZE];

unsigned int error_canary_count = 0;
unsigned int error_crc_count = 0;

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*       FUNCTIONS              */
/********************************/

void handle_data_Rx(SPIComm_TransferStatus status);
void handle_data_Tx(SPIComm_TransferStatus status);

void  RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void  SPI_Configuration(void);


/********************************/
/*       Public Functions       */
/********************************/

/**
 * @fn SPIComm_Init
 * @brief Initializes the SPI device with circular DMA on the given buffers.
 * @param buffer_Rx: pointer to the buffer where the received data is stored
 * @param buffer_Tx: pointer to the buffer where the data to send is stored
 * @param buffer_Rx_size: size of buffer_Rx in bytes
 * @param buffer_Tx_size: size of buffer_Tx in bytes
 * @return None
 */
void SPIComm_Init(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size) {

   // Save buffers' adress and size
   data_buffer_Rx_size = buffer_Rx_size;
   data_buffer_Tx_size = buffer_Tx_size;
   data_buffer_Rx = buffer_Rx;
   data_buffer_Tx = buffer_Tx;

   // System clocks configuration
   RCC_Configuration();

   // NVIC configuration
   NVIC_Configuration();

   // GPIO configuration
   GPIO_Configuration();

   // SPI configuration
   SPI_Configuration();
}

/**
 * @fn SPIComm_Start
 * @brief Starts the SPI communication.
 * @return None
 */
void SPIComm_Start(void) {
   // Enable SPIx
   SPI_Cmd(SPIx, ENABLE);
}

/**
 * @fn SPIComm_Stop
 * @brief Stops the SPI communication.
 * @return None
 */
void SPIComm_Stop(void) {
   // Make sure tranfer is complete:
   //    - avoid data corruption
   while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) != SET);
   //    - avoid unreliable BUSY flag
   while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) != RESET);
   // Disable SPIx
   SPI_Cmd(SPIx, DISABLE);
}

/**
 * @fn SPIComm_Rx_Callback
 * @brief Callback to handle Rx transfers events.
 * @return None
 */
__weak void SPIComm_Rx_Callback(SPIComm_TransferStatus status){}

/**
 * @fn SPIComm_Tx_Callback
 * @brief Callback to handle Tx transfers events.
 * @return None
 */
__weak void SPIComm_Tx_Callback(SPIComm_TransferStatus status){}




/********************************/
/*      Private Functions       */
/********************************/

/**
 * @brief  Handles the DMA interrupts.
 * @param  dma     DMA number
 * @param  channel Channel number
 * @param  flags   Interrupts flags
 * @retval None
 */
void SPIComm_DMA_Callback(DMA_Channel_TypeDef * channel, uint8_t flags) {
   SPIComm_TransferStatus status = DMA_FLAGS2STATUS(flags);

   if (channel == SPIx_DMA_Rx_Channel)
   {
      if (status == SPICOMM_TRANSFER_COMPLETE) handle_data_Rx(status);
      SPIComm_Rx_Callback(status);

   } else if (channel == SPIx_DMA_Tx_Channel)
   {
      if (status == SPICOMM_TRANSFER_COMPLETE) handle_data_Tx(status);
      SPIComm_Tx_Callback(status);

   } else {}
}

void handle_data_Rx(SPIComm_TransferStatus status) {
   uint8_t canary, crc, error_canary, error_crc;

   // extract canary and crc
   canary = frame_buffer_Rx[FRAME_CANARY_POS(data_buffer_Rx_size)];
   crc = frame_buffer_Rx[FRAME_CRC_POS(data_buffer_Rx_size)];

   // check canary
   error_canary = (Frame_Canary_Check(canary) != 0);
   error_canary_count += error_canary;

   // check crc
   error_crc = (Frame_CRC_Check(frame_buffer_Rx, data_buffer_Rx_size + FRAME_CANARY_SIZE, crc) != 0);
   error_crc_count += error_crc;

   // copy frame to data if no error
   if(!error_canary && !error_crc) memcpy(data_buffer_Rx, frame_buffer_Rx, data_buffer_Rx_size);
}

void handle_data_Tx(SPIComm_TransferStatus status) {
   // copy data to frame
   memcpy(frame_buffer_Tx, data_buffer_Tx, data_buffer_Tx_size);
   // add canary
   frame_buffer_Tx[FRAME_CANARY_POS(data_buffer_Tx_size)] = Frame_Canary_Compute();
   // add crc
   frame_buffer_Tx[FRAME_CRC_POS(data_buffer_Tx_size)] = Frame_CRC_Compute(frame_buffer_Tx, data_buffer_Tx_size + FRAME_CANARY_SIZE);
}


/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void) {
   /* Enable peripheral clocks --------------------------------------------------*/
   // Enable SPIx DMA clock
   RCC_AHBPeriphClockCmd(SPIx_DMA_CLK, ENABLE);

   // Enable GPIO clock for SPIx
   RCC_APB2PeriphClockCmd(SPIx_GPIO_CLK, ENABLE);

   // Enable SPIx Periph clock
   RCC_APB1PeriphClockCmd(SPIx_CLK, ENABLE);
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void) {
   NVIC_InitTypeDef NVIC_InitStructure;

   // 4 bit for pre-emption priority, 0 bits for subpriority
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

   // Configure and enable DMA_Rx interrupt
   NVIC_InitStructure.NVIC_IRQChannel = SPIx_DMA_Rx_Channel_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = SPIx_DMA_PRIO;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   // Configure and enable DMA_Tx interrupt
   NVIC_InitStructure.NVIC_IRQChannel = SPIx_DMA_Tx_Channel_IRQn;
   NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void) {
   GPIO_InitTypeDef GPIO_InitStructure;

   // Configure SPIx pins: SCK, MISO, MOSI
   GPIO_InitStructure.GPIO_Pin = SPIx_PIN_SCK | SPIx_PIN_MOSI;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(SPIx_GPIO, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin =  SPIx_PIN_MISO;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(SPIx_GPIO, &GPIO_InitStructure);
}

/**
  * @brief  Configures the SPI in slave mode with DMA.
  * @param  None
  * @retval None
  */
void SPI_Configuration(void) {
   SPI_InitTypeDef SPI_InitStructure;
   DMA_InitTypeDef DMA_InitStructure;

   // SPIx_Rx_DMA_Channel configuration
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPIx->DR;
   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)frame_buffer_Rx;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
   DMA_InitStructure.DMA_BufferSize = data_buffer_Rx_size + FRAME_CHECK_SIZE;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(SPIx_DMA_Rx_Channel, &DMA_InitStructure);

   // SPIx_Tx_DMA_Channel configuration
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPIx->DR;
   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)frame_buffer_Tx;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
   DMA_InitStructure.DMA_BufferSize = data_buffer_Tx_size + FRAME_CHECK_SIZE;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(SPIx_DMA_Tx_Channel, &DMA_InitStructure);

   // SPI configuration
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 0; // no CRC
   SPI_Init(SPI2, &SPI_InitStructure);

   // Enable SPIx Rx and Tx request
   SPI_I2S_DMACmd(SPIx, SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, ENABLE);

   // Enable SPIx Rx and Tx DMA channels interrupt
   DMA_ITConfig(SPIx_DMA_Rx_Channel, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE, ENABLE);
   DMA_ITConfig(SPIx_DMA_Tx_Channel, DMA_IT_HT | DMA_IT_TC | DMA_IT_TE, ENABLE);

   // Enable SPIx Rx and Tx DMA channels
   DMA_Cmd(SPIx_DMA_Rx_Channel, ENABLE);
   DMA_Cmd(SPIx_DMA_Tx_Channel, ENABLE);
}
