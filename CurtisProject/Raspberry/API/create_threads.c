/**
 * @file create_threads.c
 * @author Curtis Team
 * @brief Setup and thread creation
 */

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stdio.h>
#include <assert.h>

/********************************/
/*       INCLUDES               */
/********************************/
#include <mirroring.h>
#include <spi.h>
#include <data_interface.h>
#include <print.h>
#include <create_threads.h>
#include <go_forward.h>
#include <application_code.h>

/********************************/
/*       DEFINES                */
/********************************/





/********************************/
/*       FUNCTIONS              */
/********************************/

int create_threads(void) {

// declarations
  int error;


/**
 *@var thMirroring
 *@brief the thread that executes the mirroring data exchange between PI ans Nucleo via spi
 */
/**
 *@var thPrint
 *@brief the thread that prints the information sent and received by the PI
 */
/**
 *@var thGoFwd
 *@brief the thread that executes untill the expected distance is travelled if distance is > 0
 */
/**
 *@var thAppli
 *@brief the thread that executes the Application 
 */

  pthread_t thMirroring, thPrint, thGoFwd, thAppli;  

/**
 *@brief the threads context
 */
  pthread_attr_t myAttr;

/**
 *@var prioMirroring
 *@brief the struct containing the priority for the thread thMirroring
 */
/**
 *@var prioPrint
 *@brief the struct containing the priority for thPrint
 */
/**
 *@var prioGoFwd
 *@brief the struct containing the priority for thGoFwd
 */
/**
 *@var prioAppli
 *@brief the struct containing the priority for thAppli
 */
  struct sched_param prioMirroring, prioPrint, prioGoFwd, prioAppli;



// init the threads context and set the queue policy
  pthread_attr_init(&myAttr);
  pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);


// Application
  prioAppli.sched_priority = PRIO_APPLI;
  error = pthread_attr_setschedparam(&myAttr, &prioAppli);
  error = pthread_create(&thAppli, &myAttr, Application, 0);
  assert (error == 0);


// print  
  prioPrint.sched_priority = PRIO_PRINT;
  error = pthread_attr_setschedparam(&myAttr, &prioPrint);
  error = pthread_create(&thPrint, &myAttr, print, 0);
  assert (error == 0);

// mirroring
  prioMirroring.sched_priority = PRIO_MIRRORING;
  error = pthread_attr_setschedparam(&myAttr, &prioMirroring);
  error = pthread_create(&thMirroring, &myAttr, mirroringPI, 0);
  assert (error == 0);

// Thread_goForward
  prioGoFwd.sched_priority = PRIO_GO_FWD;
  error = pthread_attr_setschedparam(&myAttr, &prioGoFwd);
  error = pthread_create(&thGoFwd, &myAttr, thread_goForward, 0);
  assert (error == 0);





// joining threads
  error = pthread_join(thMirroring, NULL);
  assert (error == 0);

  error = pthread_join(thPrint, NULL);
  assert (error == 0);

  error = pthread_join(thGoFwd, NULL);
  assert (error == 0);

  error = pthread_join(thAppli, NULL);
  assert (error == 0);

  return error;
}

