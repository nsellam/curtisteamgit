#ifndef MIRRORING_H
#define MIRRORING_H

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
 * @fn Mirroring_Init
 * @brief Initialize the mirroring for both data_STM (sent) and data_PI (received).
 * @return None
 */

void Mirroring_Init(void);

/**
 * @fn Mirroring_Start
 * @brief Starts the mirroring.
 * @return None
 */

void Mirroring_Start(void);

/**
 * @fn Mirroring_Stop
 * @brief Stops the mirroring.
 * @return None
 */

void Mirroring_Stop(void);

#endif // MIRRORING_H
