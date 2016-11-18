#ifndef MIRRORING_PI_H
#define MIRRORING_PI_H

/**
 * @file mirroring_pi.h
 * @author Curtis Team
 * @brief header for mirroring_pi
 */

/********************************/
/*       LIBRARIES              */
/********************************/

/************************
 *      STRUCTURES      *
 ************************/

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn mirroring_init
 * @brief initializes the mirroring
 * @return ??
 */
int mirroring_init(void);

/**
 * @fn sync_data_PI
 * @brief synchronizes the value of the sensors / errors
 * @return size of the packet
 * @retval -1 if error
 */
int sync_data_PI(void);

/**
 * @fn sync_data_STM
 * @brief synchronizes the value of the actuators / errors
 * @return size of the data received
 * @retval -1 if error?
 */
int sync_data_STM(void);

#endif //MIRRORING_PI_H
