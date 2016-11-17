/**
 * @file mirroring_st.c
 * @author Curtis team
 * @brief service layer for the STM32
 * Synchronizes data by sending values of sensors and receiving values of actuators
 */

#include "mirroring.h"
//#include "SPI.h"

volatile sensors_t sensors, *psensors = &sensors;
volatile actuators_t actuators, *pactuators = &actuators;

/**
 * @fn sync_sensors
 * @brief sends the value of the sensors to the Raspberry Pi
 * @return 0 if successful / -1 if error
 */
int sync_sensors(void) {
return 0;//SPI_send((uint8_t*)psensors, sizeof(sensors));
}

/**
 * @fn sync_actuators
 * @brief receives the value of the actuators from the Raspberry Pi
 * @return 0 if successful / -1 if error
 */
int sync_actuators(void) {
return 0;//SPI_receive((uint8_t*)pactuators, sizeof(actuators));
}
