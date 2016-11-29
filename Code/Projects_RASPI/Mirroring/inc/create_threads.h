
/**
 * @file create_threads.h
 * @author Curtis Team
 * @brief header of create_threads.c
 */

#ifndef CREATE_THREDS_H

#define CREATE_THREADS_H


/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>


/********************************/
/*       DEFINES                */
/********************************/

/**
 * @def PRIO_MIRRORING
 * @brief the priority of thread mirroring
 */ 
#define PRIO_MIRRORING 30

/**
 * @def PRIO_PRINT
 * @brief the priority of thread print
 */ 
#define PRIO_PRINT 4

/**
 * @def PRIO_DEMO
 * @brief the priority of thread demo_mirroring
 */ 
#define PRIO_DEMO 8

/********************************/
/*       VARIABLES              */
/********************************/

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn create_threads
* @brief tocreate and start threads
* @return an error code
* @retval -1 in case of an error / 0 otherwise
*/

int create_threads(void);


#endif
