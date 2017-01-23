#ifndef GO_FORWARD_H
#define GO_FORWARD_H

/**
 * @file go_forward.h
 * @author Curtis Team
 * @brief header of go_forward.c
 */

#include <stdint.h>
#include <pthread.h>

/************************
 *      DEFINES         *
 ************************/

/** 
* @brief code meaning we want the car to go backward
*/
#define BWD -1

/** 
* @brief code meaning we want the car to stop
*/
#define STOP 0

/** 
* @brief code meaning we want the car to go forward
*/
#define FWD 1

/************************
 *      VARIABLES       *
 ************************/

/**
 * @var T1_goFwd
 * @brief the time of previous 'wait_period' function call inside the thread mirroringPI (time reference for waitPeriod)
 */

/**
 * @var T2_goFwd
 * @brief the time of latest 'wait_period' function call inside the thread mirroringPI
 */


struct timespec T1_GoFwd, T2_GoFwd;

/**
 * @var elapsedTime
 * @brief  elapsed time between two thread periods
 */
int elapsedTimeGoFwd;



/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @brief periodic thread to go forward for a certain distance 
 * @retval none
 */
void * thread_goForward (void *arg) ;

#endif 