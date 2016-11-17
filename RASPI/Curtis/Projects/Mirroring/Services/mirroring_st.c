/**
 * @file mirroring_st.c
 * @author Curtis team
 * @brief service layer for the STM32
 * Synchronizes data by sending values of sensors and receiving values of actuators
 */

#include "mirroring.h"
#include "SPI.h"

/**
 * @fn sync_sensors
 * @brief sends the value of the sensors to the Raspberry Pi
 * @return 0 if successful / -1 if error
 */
int sync_sensors(void) {
return SPI_send(pSensors, sizeof(Sensors));
}

/**
 * @fn sync_actuators
 * @brief receives the value of the actuators from the Raspberry Pi
 * @return 0 if successful / -1 if error
 */
int sync_actuators(void) {
return SPI_receive(pActuators, sizeof(Actuators));
}
