/**
 * @file mirroring_st.c
 * @author Curtis team
 * @brief service layer for the STM32
 * Synchronizes data by sending the data of the STM and receiving the data of the RASPI
 */
#include <data.h>

#include "mirroring.h"

#include "spi.h"

uint8_t buffer[DATA_SIZE_MAX];
uint8_t buffer2[DATA_SIZE_MAX] = {0};

void Mirroring_init(void) {
   buffer2[3] = 0x06;
   SPI_init(buffer, buffer2, DATA_SIZE_MAX, DATA_SIZE_MAX);
}

void Mirroring_start(void) {
   SPI_start();
}

void Mirroring_stop(void) {
   SPI_stop();
}
