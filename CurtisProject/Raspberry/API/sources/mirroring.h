#ifndef MIRRORING_H
#define MIRRORING_H

/**
 * @file mirroring.h
 * @author Curtis Team
 * @brief common header to mirroring_pi and mirroring_st
 * This header contains structures of sensors and actuators
 */

#include <stdint.h>
#include <pthread.h>

/************************
 *      STRUCTURES      *
 ************************/



/************************
 *      VARIABLES       *
 ************************/

/**
 * @var T1
 * @brief the time of previous 'wait_period' function call inside the thread mirroringPI (time reference for waitPeriod)-> struct timespec
 */

/**
 * @var T2
 * @brief the time of latest 'wait_period' function call inside the thread mirroringPI-> struct timespec
 */


struct timespec T1, T2;

/**
 * @var elapsedTime
 * @brief  elapsed time between two thread periods
 */
int elapsedTime;


/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn mirroringPI
 * @brief periodic thread running the mirroring on PI
 * @return not used
 */
void * mirroringPI (void *arg) ;

#endif 