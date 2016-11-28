#ifndef PRINT_H
#define PRINT_H

/**
 * @file print.h
 * @author Curtis Team
 * @brief header of print
 */

#include <stdint.h>
#include <pthread.h>

/************************
 *      STRUCTURES      *
 ************************/

extern int k;


/************************
 *      VARIABLES       *
 ************************/

/**
 * @var T1_Print
 * @brief the time of previous 'wait_period' function call inside the thread mirroringPI (time reference for waitPeriod)-> struct timespec
 */

/**
 * @var T2_Print
 * @brief the time of latest 'wait_period' function call inside the thread mirroringPI-> struct timespec
 */


struct timespec T1_Print, T2_Print;

/**
 * @var elapsedTime
 * @brief  elapsed time between two thread periods
 */
int elapsedTimePrint;


/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn thread
 * @brief periodic thread running the printing of shared variables 
 * @return not used
 */
void * print (void *arg) ;

#endif 