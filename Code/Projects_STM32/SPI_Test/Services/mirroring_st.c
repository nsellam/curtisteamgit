/**
 * @file mirroring_st.c
 * @author Curtis team
 * @brief service layer for the STM32
 * Synchronizes data by sending the data of the STM and receiving the data of the RASPI
 */
#include <data.h>

#include "mirroring.h"

#include "spicomm_st.h"

#define BUFFER_RX_SIZE (DATA_SIZE_MAX)
#define BUFFER_TX_SIZE (DATA_SIZE_MAX)

uint8_t buffer_Rx[BUFFER_RX_SIZE];
uint8_t buffer_Tx[BUFFER_TX_SIZE];

/********************************/
/*       Public Functions       */
/********************************/

void mirroring_init(void) {
   pdata_PI  = (data_PI_t *)buffer_Rx;
   pdata_STM = (data_STM_t *)buffer_Tx;
   SPIComm_init((uint8_t *)buffer_Rx, (uint8_t *)buffer_Tx, BUFFER_RX_SIZE, BUFFER_TX_SIZE);
}

void mirroring_start(void) {
   SPIComm_start();
}

void mirroring_stop(void) {
   SPIComm_stop();
}
