#ifndef DEMO_MIRRORING_H
#define DEMO_MIRRORING_H

/**
 * @file demo_mirroring.h
 * @author Curtis Team
 * @brief header of demo_mirroring.c
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
 * @var T1_demo
 * @brief the time of previous 'wait_period' function call inside the thread mirroringPI (time reference for waitPeriod)-> struct timespec
 */

/**
 * @var T2_demo
 * @brief the time of latest 'wait_period' function call inside the thread mirroringPI-> struct timespec
 */


struct timespec T1_demo, T2_demo;

/**
 * @var elapsed_time_demo
 * @brief  elapsed time between two thread periods
 */
int elapsed_time_demo;


/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn thread
 * @brief periodic thread running the printing of shared variables 
 * @return not used
 */
void * demo_mirroring (void *arg) ;

#endif 