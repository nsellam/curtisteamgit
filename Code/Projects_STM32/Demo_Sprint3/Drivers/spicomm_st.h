
#ifndef _SPICOMM_H_
#define _SPICOMM_H_

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
   TRANSFER_UNKNOWN  = -1,
   TRANSFER_COMPLETE =  0,
   TRANSFER_HALF     =  1,
   TRANSFER_ERROR    =  2
} SPIComm_TransferStatus;

/********************************/
/*       FUNCTIONS              */
/********************************/


void SPIComm_Init(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t buffer_Rx_size, size_t buffer_Tx_size);

void SPIComm_Start(void);
void SPIComm_Stop(void);

void SPIComm_Rx_Callback(SPIComm_TransferStatus status);
void SPIComm_Tx_Callback(SPIComm_TransferStatus status);

#endif // _SPICOMM_H_
