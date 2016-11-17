#ifndef MIRRORING_H
#define MIRRORING_H

/**
 * @file mirroring.h
 * @author Curtis Team
 * @brief header for mirroring_pi
 */

#include <stdint.h>

/************************
 *      STRUCTURES      *
 ************************/

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn sync_data_Pi
 * @brief synchronizes the value of the sensors / errors
 * @return size?, -1 if error
 */
int sync_data_Pi(void);

/**
 * @fn sync_data_STM
 * @brief synchronizes the value of the actuators / errors
 * @return size?, -1 if error
 */
int sync_data_STM(void);

#endif //MIRRORING_H
