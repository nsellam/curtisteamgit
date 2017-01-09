/**
 * @file    spi_comm.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle communication threw SPI  
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SPI_COMM_H
#define _SPI_COMM_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
   TRANSFER_UNKNOWN  = -1,
   TRANSFER_COMPLETE =  0,
   TRANSFER_HALF     =  1,
   TRANSFER_ERROR    =  2
} SPIComm_TransferStatus;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SPIComm_QuickInit(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size);

void SPIComm_Start(void);
void SPIComm_Stop(void);

void SPIComm_Rx_Callback(SPIComm_TransferStatus status);
void SPIComm_Tx_Callback(SPIComm_TransferStatus status);

#endif // _SPI_COMM_H
