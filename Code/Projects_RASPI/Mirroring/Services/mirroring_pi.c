/**
 * @file mirroring_pi.c
 * @author Curtis team
 * @brief service layer for the Raspberry Pi
 * Synchronizes data by sending values of actuators and receiving values of sensors
 */

#include "mirroring.h"
#include "spi.h"

/************************
 *      VARIABLES       *
 ************************/

sensors_t sensors, *psensors = &sensors;
actuators_t actuators, *pactuators = &actuators;

/************************
 *      FUNCTIONS       *
 ************************/

/* for the test */
int init_actuators(void) {
  pactuators->steering_stop_sensor_R = '0';
  pactuators->steering_stop_sensor_L = '0';
  pactuators->motor_dir = '0';
  pactuators->led = '0';
  return 0;
}

/**
 * @fn sync_actuators
 * @brief sends the value of the actuators to the STM32
 * @return 0 if successful / -1 if error
 */
int sync_actuators(void) {
return SPI_send((uint8_t*)pactuators, sizeof(actuators_t));
}

/**
 * @fn sync_sensors
 * @brief receives the value of the sensors from the STM32
 * @return 0 if successful / -1 if error
 */
int sync_sensors(void) {
return SPI_receive((uint8_t*)psensors, sizeof(sensors_t));
}
