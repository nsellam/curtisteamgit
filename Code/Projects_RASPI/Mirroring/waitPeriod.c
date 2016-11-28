/**
 * @file waitPeriod.c
 * @author Curtis_team
 *@brief provides a function to set any thread periodic
 */


/********************************/
/*       LIBRARIES              */
/********************************/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/********************************/
/*       HEADER_FILES           */
/********************************/

#include <waitPeriod.h>
#include <unistd.h>

/********************************/
/*        DEFINES               */
/********************************/

/**
 * @def DRIFT_COMPENSATION
 * @brief coef. to have an exact thread period
 */
#define DRIFT_COMPENSATION 40000

/********************************/
/*       VARIABLES              */
/********************************/

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*      MUTEX                   */
/********************************/

/********************************/
/*      SEMAPHORES              */
/********************************/


/********************************/
/*       FUNCTIONS              */
/********************************/

void waitPeriod (int period_ns,struct timespec * pT1, struct timespec * pT2){

    // Reset elapsed_time and store reference time for next call in pT2
    int elapsedTime = 0;
    clock_gettime(CLOCK_REALTIME, pT2);   // ref for next fct call

    // Wait for accurate tempo begin time
     do{
        // Update elapsed_time
        usleep(1);
        clock_gettime(CLOCK_REALTIME, pT2);

        //compute time elapsed since last time the thread has been executed
        elapsedTime = (pT2->tv_sec - pT1->tv_sec)*1000000000;
        elapsedTime +=  (pT2->tv_nsec - pT1->tv_nsec);
    }while (elapsedTime <= period_ns - DRIFT_COMPENSATION);
}




