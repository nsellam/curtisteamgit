/**
 * @file mirroring.h
 * @author Curtis Team
 * @brief Common header to mirroring_pi and mirroring_st
 */

#ifndef MIRRORING_H
#define MIRRORING_H

#include <stdint.h>
#include "data.h"

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @brief Initialize the mirroring for both data_STM (sent) and data_PI (received).
 * @return None
 */

void mirroring_init(void);

/**
 * @brief Starts the mirroring.
 * @return None
 */

void mirroring_start(void);

/**
 * @brief Stops the mirroring.
 * @return None
 */

void mirroring_stop(void);

#endif // MIRRORING_H

