/**
 * @file    spi_comm.c
 * @author  Curtis Team
 * @brief   Functions to handle communication threw SPI  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "spi_comm.h"
#include "frame_check.h"
#include "nvic.h"
#include "gpio.h"
#include "spi.h"
#include "dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPICOMM_BUFFER_SIZE_MAX 256


#define FRAME_CANARY_POS(length) ((length) + 0)
#define FRAME_CRC_POS(length)    (FRAME_CANARY_POS(length) + FRAME_CANARY_SIZE)

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
#define SPIx_DMA_PRIO            1

#define DMA_FLAGS2STATUS(flags) (((flags) & DMA_FLAG_TE) ? TRANSFER_ERROR    :\
                                (((flags) & DMA_FLAG_HT) ? TRANSFER_HALF     :\
                                (((flags) & DMA_FLAG_TC) ? TRANSFER_COMPLETE : TRANSFER_UNKNOWN)))

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
size_t data_buffer_Rx_size;
size_t data_buffer_Tx_size;
uint8_t *data_buffer_Rx;
uint8_t *data_buffer_Tx;

uint8_t frame_buffer_Rx[SPICOMM_BUFFER_SIZE_MAX + FRAME_CHECK_SIZE];
uint8_t frame_buffer_Tx[SPICOMM_BUFFER_SIZE_MAX + FRAME_CHECK_SIZE];

int error_canary_num = 0;
int error_crc_num = 0;

/* Private function prototypes -----------------------------------------------*/
void handle_data_Rx(SPIComm_TransferStatus status);
void handle_data_Tx(SPIComm_TransferStatus status);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Initializes the SPI device with circular DMA on the given buffers.
 * @param   buffer_Rx Pointer to the buffer where the received data is stored
 * @param   buffer_Tx Pointer to the buffer where the data to send is stored
 * @param   buffer_Rx_size Size of buffer_Rx in bytes
 * @param   buffer_Tx_size Size of buffer_Tx in bytes
 * @retval  None
 */
void SPIComm_QuickInit(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size) {
    // Save buffers' adress and size
    data_buffer_Rx_size = buffer_Rx_size;
    data_buffer_Tx_size = buffer_Tx_size;
    data_buffer_Rx = buffer_Rx;
    data_buffer_Tx = buffer_Tx;

    // System clocks configuration
    RCC_AHBPeriphClockCmd(SPIx_DMA_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(SPIx_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(SPIx_CLK, ENABLE);

    // NVIC configuration
    NVIC_QuickInit(SPIx_DMA_Rx_Channel_IRQn, SPIx_DMA_PRIO);

    // GPIO configuration
    GPIO_QuickInit(SPIx_GPIO, SPIx_PIN_SCK, GPIO_Mode_IN_FLOATING);
    GPIO_QuickInit(SPIx_GPIO, SPIx_PIN_MOSI, GPIO_Mode_IN_FLOATING);
    GPIO_QuickInit(SPIx_GPIO, SPIx_PIN_MISO, GPIO_Mode_AF_PP);

    // SPI configuration
    SPI_QuickInit(*SPIx, SPI_Mode_Slave);
    
    // DMA configuration 
    DMA_QuickInit_Buffer2Periph(SPIx_DMA_Tx_Channel, SPIx_DR_Base, (uint32_t)frame_buffer_Tx, data_buffer_Tx_size + FRAME_CHECK_SIZE, data_buffer_Tx_size + FRAME_CHECK_SIZE);
    DMA_QuickInit_Periph2Buffer(SPIx_DMA_Rx_Channel, SPIx_DR_Base, (uint32_t)frame_buffer_Rx, data_buffer_Rx_size + FRAME_CHECK_SIZE, data_buffer_Tx_size + FRAME_CHECK_SIZE);
}


/**
 * @brief   Starts the SPI communication.
 * @retval  None
 */
void SPIComm_Start(void) {
   SPI_Cmd(SPIx, ENABLE);
}

/**
 * @brief   Stops the SPI communication.
 * @retval  None
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
 * @brief   Callback to handle Rx transfers events.
 * @retval  None
 */
__weak void SPIComm_Rx_Callback(SPIComm_TransferStatus status){}

/**
 * @brief   Callback to handle Tx transfers events.
 * @retval  None
 */
__weak void SPIComm_Tx_Callback(SPIComm_TransferStatus status){}
    
/* Private functions ---------------------------------------------------------*/
