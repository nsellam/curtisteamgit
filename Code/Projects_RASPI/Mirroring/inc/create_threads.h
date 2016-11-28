
#ifndef CREATE_THREDS_H

#define CREATE_THREADS_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>


/********************************/
/*       DEFINES                */
/********************************/
#define PRIO_MIRRORING 30
#define PRIO_PRINT 4
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