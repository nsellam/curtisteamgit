/**
 * @file mirroring_pi.c
 * @author Curtis team
 * @brief service layer for the Raspberry Pi
 * Synchronizes data by sending values of actuators and receiving values of sensors
 */

#include "mirroring.h"
#include "spi.h"
#include "data.h"

/************************
 *      VARIABLES       *
 ************************/

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn sync_data_Pi
 * @brief synchronizes the value of the sensors / errors
 * @return size?, -1 if error
 */
int sync_data_Pi(void) {
return SPI_send((uint8_t*)pdata_Pi, sizeof(data_Pi_t));
}

/**
 * @fn sync_data_STM
 * @brief synchronizes the value of the actuators / errors
 * @return size?, -1 if error
 */
int sync_data_STM(void) {
return SPI_receive((uint8_t*)pdata_STM, sizeof(data_STM_t));
}


