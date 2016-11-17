
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
#define SPI_SLAVE                    SPI2
#define SPI_SLAVE_CLK                RCC_APB1Periph_SPI2
#define SPI_SLAVE_GPIO               GPIOB
#define SPI_SLAVE_GPIO_CLK           RCC_APB2Periph_GPIOB
#define SPI_SLAVE_PIN_NSS            GPIO_Pin_12
#define SPI_SLAVE_PIN_SCK            GPIO_Pin_13
#define SPI_SLAVE_PIN_MISO           GPIO_Pin_14
#define SPI_SLAVE_PIN_MOSI           GPIO_Pin_15
#define SPI_SLAVE_DMA                DMA1
#define SPI_SLAVE_DMA_CLK            RCC_AHBPeriph_DMA1
#define SPI_SLAVE_Rx_DMA_Channel     DMA1_Channel4
#define SPI_SLAVE_Tx_DMA_Channel     DMA1_Channel5
#define SPI_SLAVE_DR_Base            (SPI2_BASE + 0x0C)

/********************************/
/*       VARIABLES              */
/********************************/
size_t SPI_SLAVE_BufferSize_Rx;
size_t SPI_SLAVE_BufferSize_Tx;
uint8_t *SPI_SLAVE_Buffer_Rx;
uint8_t *SPI_SLAVE_Buffer_Tx;

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*       FUNCTIONS              */
/********************************/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void SPI_Configuration(void);


/**
* @fn SPI_init
* @brief initializes SPI device 
* @param length: the data to send -> int
* @return : 0 if successful / -1 if error -> int
*/

int SPI_init(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t bufferSize_Rx, size_t bufferSize_Tx) {

   // Save buffers adress and size
   SPI_SLAVE_BufferSize_Rx = bufferSize_Rx;
   SPI_SLAVE_BufferSize_Tx = bufferSize_Tx;
   SPI_SLAVE_Buffer_Rx = buffer_Rx;
   SPI_SLAVE_Buffer_Tx = buffer_Tx;

   // System clocks configuration
   RCC_Configuration();

   // GPIO configuration
   GPIO_Configuration();

   // SPI configuration
   SPI_Configuration();

   return 0;
}

/**
* @fn SPI_start
* @brief start the SPI communication
* @return : 0 if successful / -1 if error -> int
*/

int SPI_start(void) {
   // Enable SPI_SLAVE
   SPI_Cmd(SPI_SLAVE, ENABLE);
   return 0;
}

/**
* @fn SPI_stop
* @brief stop the SPI communication
* @return : 0 if successful / -1 if error -> int
*/

int SPI_stop(void) {
   // Make sure tranfer is complete:
   // - avoid data corruption
   while(SPI_I2S_GetFlagStatus(SPI_SLAVE, SPI_I2S_FLAG_TXE) !=   SET);
   // - avoid unreliable BUSY flag
   while(SPI_I2S_GetFlagStatus(SPI_SLAVE, SPI_I2S_FLAG_BSY) != RESET);
   // Disable SPI_SLAVE
   SPI_Cmd(SPI_SLAVE, DISABLE);
   return 0;
}





/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void) {
   /* Enable peripheral clocks --------------------------------------------------*/
   // Enable SPI_SLAVE DMA clock
   RCC_AHBPeriphClockCmd(SPI_SLAVE_DMA_CLK, ENABLE);

   // Enable GPIO clock for SPI_SLAVE
   RCC_APB2PeriphClockCmd(SPI_SLAVE_GPIO_CLK, ENABLE);

   // Enable SPI_SLAVE Periph clock
   RCC_APB1PeriphClockCmd(SPI_SLAVE_CLK, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void) {
   GPIO_InitTypeDef GPIO_InitStructure;

   // Configure SPI_SLAVE pins: SCK, MISO, MOSI
   GPIO_InitStructure.GPIO_Pin = SPI_SLAVE_PIN_SCK | SPI_SLAVE_PIN_MOSI;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin =  SPI_SLAVE_PIN_MISO;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(SPI_SLAVE_GPIO, &GPIO_InitStructure);
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

   // SPI_SLAVE_Rx_DMA_Channel configuration
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI_SLAVE_DR_Base;
   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI_SLAVE_Buffer_Rx;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
   DMA_InitStructure.DMA_BufferSize = SPI_SLAVE_BufferSize_Rx;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(SPI_SLAVE_Rx_DMA_Channel, &DMA_InitStructure);

   // SPI_SLAVE_Tx_DMA_Channel configuration
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SPI_SLAVE_DR_Base;
   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI_SLAVE_Buffer_Tx;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
   DMA_InitStructure.DMA_BufferSize = SPI_SLAVE_BufferSize_Tx;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(SPI_SLAVE_Tx_DMA_Channel, &DMA_InitStructure);

   // SPI configuration
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 0;
   SPI_Init(SPI2, &SPI_InitStructure);

   // Enable SPI_SLAVE Rx and Tx request
   SPI_I2S_DMACmd(SPI_SLAVE, SPI_I2S_DMAReq_Rx, ENABLE);
   SPI_I2S_DMACmd(SPI_SLAVE, SPI_I2S_DMAReq_Tx, ENABLE);
 
   // Enable SPI_SLAVE_Rx_DMA_Channel
   DMA_Cmd(SPI_SLAVE_Rx_DMA_Channel, ENABLE);
   // Enable SPI_SLAVE_Tx_DMA_Channel
   DMA_Cmd(SPI_SLAVE_Tx_DMA_Channel, ENABLE);
}
