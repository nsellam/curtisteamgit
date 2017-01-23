/**
 * @file waitPeriod.h
 * @author curtisTeam
 * @brief header of the file waitPeriod.c
 */



#ifndef WAIT_PERIOD_H
#define WAIT_PERIOD_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>


/********************************/
/*       ALIAS                  */
/********************************/

/********************************/
/*       GLOBAL VARIABLES       */
/********************************/


/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*      (GLOBAL) MUTEX          */
/********************************/



/********************************/
/*      SEMAPHORES              */
/********************************/


/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn waitPeriod
* @brief to call at the beginning of a thread ensures a precise periodicity of the thread
* @param period_ns : the desired thread period in nano sec. -> int
* @param pElapsedTime : pointer to the elapsed time variable -> pointer
* @param pT1 : pointer to the time of previous 'wait_period' function call -> struct timespec
* @param pT2 : pointer to current 'wait_period' function call time -> struct timespec
* @param pT3 : pointer to current time -> struct timespec
* @return : nothing
*/

void waitPeriod (int period_ns, struct timespec * pT1, struct timespec * pT2);

#endif