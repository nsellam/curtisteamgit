/**
 * @file mirroring_st.c
 * @author Curtis team
 * @brief service layer for the STM32
 * Synchronizes data by sending values of sensors and receiving values of actuators
 */

#include "mirroring.h"
#include "spi.h"

volatile sensors_t sensors, *psensors = &sensors;
volatile actuators_t actuators, *pactuators = &actuators;

void Mirroring_init(void) {
   SPI_init((uint8_t*)pactuators, (uint8_t*)psensors, sizeof(actuators), sizeof(sensors));
}

void Mirroring_start(void) {
   SPI_start();
}

void Mirroring_stop(void) {
   SPI_stop();
}
