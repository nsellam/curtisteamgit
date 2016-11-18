#ifndef _MIRRORING_H_
#define _MIRRORING_H_

/**
 * @file mirroring.h
 * @author Curtis Team
 * @brief common header to mirroring_pi and mirroring_st
 */

#include <stdint.h>
#include "data.h"

/************************
 *      FUNCTIONS       *
 ************************/

/**
* @fn Mirroring_init
* @brief Initialize the mirroring for both data_STM (sent) and data_PI (received).
* @return None
*/

void Mirroring_init(void);

/**
* @fn Mirroring_start
* @brief Starts the mirroring.
* @return None
*/

void Mirroring_start(void);

/**
* @fn Mirroring_stop
* @brief Stops the mirroring.
* @return None
*/

void Mirroring_stop(void);

#endif // _MIRRORING_H_
