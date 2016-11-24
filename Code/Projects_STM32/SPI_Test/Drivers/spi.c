
/********************************/
/*       LIBRARIES              */
/********************************/
#include "spi.h"

#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/********************************/
/*       ALIAS                  */
/********************************/

#define SPIx_DR_Offset           0x0C
#define SPIx_DR_Base             (SPI2_BASE + SPIx_DR_Offset)

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
#define SPIx_DMA_SUBPRIO         1

/********************************/
/*       VARIABLES              */
/********************************/
size_t SPIx_BufferSize_Rx;
size_t SPIx_BufferSize_Tx;
uint8_t *SPIx_Buffer_Rx;
uint8_t *SPIx_Buffer_Tx;

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*       FUNCTIONS              */
/********************************/
void  RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void  SPI_Configuration(void);


/**
* @fn SPI_init
* @brief Initializes the SPI device.
* @param buffer_Rx: pointer to the buffer where the received data is stored
* @param buffer_Tx: pointer to the buffer where the data to send is stored
* @param bufferSize_Rx: size of buffer_Rx in bytes
* @param bufferSize_Tx: size of buffer_Tx in bytes
* @return None
*/

void SPI_init(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t bufferSize_Rx, size_t bufferSize_Tx) {

   // Save buffers' adress and size
   SPIx_BufferSize_Rx = bufferSize_Rx;
   SPIx_BufferSize_Tx = bufferSize_Tx;
   SPIx_Buffer_Rx = buffer_Rx;
   SPIx_Buffer_Tx = buffer_Tx;

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
* @fn SPI_start
* @brief Starts the SPI communication.
* @return None
*/

void SPI_start(void) {
   // Enable SPIx
   SPI_Cmd(SPIx, ENABLE);
}

/**
* @fn SPI_stop
* @brief Stops the SPI communication.
* @return None
*/

void SPI_stop(void) {
   // Make sure tranfer is complete:
   //    - avoid data corruption
   while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) != SET);
   //    - avoid unreliable BUSY flag
   while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) != RESET);
   // Disable SPIx
   SPI_Cmd(SPIx, DISABLE);
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

   // 0 bit for pre-emption priority, 4 bits for subpriority
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

   // Configure and enable DMA_Rx interrupt
   NVIC_InitStructure.NVIC_IRQChannel = SPIx_DMA_Rx_Channel_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = SPIx_DMA_SUBPRIO;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   // Configure and enable DMA_Tx interrupt
   NVIC_InitStructure.NVIC_IRQChannel = SPIx_DMA_Tx_Channel_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
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
   SPI_InitTypeDef  SPI_InitStructure;
   DMA_InitTypeDef  DMA_InitStructure;
   //NVIC_InitTypeDef NVIC_InitStructure;

   // SPIx_Rx_DMA_Channel configuration
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_Base;
   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPIx_Buffer_Rx;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
   DMA_InitStructure.DMA_BufferSize = SPIx_BufferSize_Rx;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(SPIx_DMA_Rx_Channel, &DMA_InitStructure);

   // SPIx_Tx_DMA_Channel configuration
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPIx_DR_Base;
   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPIx_Buffer_Tx;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
   DMA_InitStructure.DMA_BufferSize = SPIx_BufferSize_Tx;
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
   SPI_I2S_DMACmd(SPIx, SPI_I2S_DMAReq_Rx, ENABLE);
   SPI_I2S_DMACmd(SPIx, SPI_I2S_DMAReq_Tx, ENABLE);

   // Enable SPIx_Rx_DMA_Channel
   DMA_Cmd(SPIx_DMA_Rx_Channel, ENABLE);
   // Enable SPIx_Tx_DMA_Channel
   DMA_Cmd(SPIx_DMA_Tx_Channel, ENABLE);
}
