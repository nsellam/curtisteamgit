/**
 * @file mirroring_st.c
 * @author Curtis team
 * @brief service layer for the STM32
 * Synchronizes data by sending the data of the STM and receiving the data of the RASPI
 */
#include <data.h>

#include "mirroring.h"

#include "spi.h"

   uint8_t buffer[(sizeof(data_STM_t) > sizeof(data_PI_t)) ? sizeof(data_STM_t) : sizeof(data_PI_t)];

void Mirroring_init(void) {
   SPI_init(buffer, buffer, data_size_max, data_size_max);
}

void Mirroring_start(void) {
   SPI_start();
}

void Mirroring_stop(void) {
   SPI_stop();
}
