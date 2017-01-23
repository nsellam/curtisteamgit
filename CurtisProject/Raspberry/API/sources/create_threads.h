
#ifndef CREATE_THREADS_H

#define CREATE_THREADS_H

/**
 * @file create_threads.h
 * @author Curtis Team
 * @brief header of create_threads.c
 */

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>
#include <pthread.h>


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
 * @def PRIO_GO_FORWARD
 * @brief the priority of thread goForward
 */ 
#define PRIO_GO_FWD 10

/**
 * @def PRIO_APPLICATION
 * @brief the priority of thread Application
 */ 
#define PRIO_APPLI 5

/********************************/
/*       VARIABLES              */
/********************************/

  extern pthread_attr_t myAttr;

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn create_threads
* @brief to create and start our API threads and the Application thread
* @return an error code
* @retval -1 in case of an error / 0 otherwise
*/

int create_threads(void);


#endif