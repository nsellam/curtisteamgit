/**
 * @file spicomm.h
 * @author Curtis Team
 * @brief SPI communication module
 */

#ifndef SPICOMM_H
#define SPICOMM_H

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stdint.h>
#include <stddef.h>

/********************************/
/*       ALIAS                  */
/********************************/

/********************************/
/*       VARIABLES              */
/********************************/

/********************************/
/*       STRUCTURES             */
/********************************/

typedef enum {
   SPICOMM_TRANSFER_UNKNOWN  = -1,
   SPICOMM_TRANSFER_COMPLETE =  0,
   SPICOMM_TRANSFER_HALF     =  1,
   SPICOMM_TRANSFER_ERROR    =  2
} SPIComm_TransferStatus;

/********************************/
/*       FUNCTIONS              */
/********************************/


void SPIComm_Init(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size);

void SPIComm_Start(void);
void SPIComm_Stop(void);

void SPIComm_Rx_Callback(SPIComm_TransferStatus status);
void SPIComm_Tx_Callback(SPIComm_TransferStatus status);

#endif // SPICOMM_H
