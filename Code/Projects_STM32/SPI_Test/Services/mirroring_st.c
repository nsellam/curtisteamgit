/**
 * @file mirroring_st.c
 * @author Curtis team
 * @brief service layer for the STM32
 * Synchronizes data by sending the data of the STM and receiving the data of the RASPI
 */

#include "mirroring.h"

#include "spi.h"
#include "data.h"

void Mirroring_init(void) {
   SPI_init((uint8_t*)pdata_PI, (uint8_t*)pdata_STM, sizeof(data_PI_t), sizeof(data_STM_t));
}

void Mirroring_start(void) {
   SPI_start();
}

void Mirroring_stop(void) {
   SPI_stop();
}
