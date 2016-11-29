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
#include <data.h>
#include <print.h>
#include <create_threads.h>
#include <demo_mirroring.h>

/********************************/
/*       DEFINES                */
/********************************/





/********************************/
/*       FUNCTIONS              */
/********************************/

int create_threads(void) {

// declarations
  int error;
  pthread_t thMirroring, thPrint, thDemo;  
  pthread_attr_t myAttr;
  struct sched_param prioMirroring, prioPrint, prioDemo;

// 
  pthread_attr_init(&myAttr);
  pthread_attr_setschedpolicy(&myAttr, SCHED_FIFO);

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

// demo_mirroring
  prioDemo.sched_priority = PRIO_DEMO;
  error = pthread_attr_setschedparam(&myAttr, &prioDemo);
  error = pthread_create(&thDemo, &myAttr, demo_mirroring, 0);
  assert (error == 0);


// joining threads
  error = pthread_join(thMirroring, NULL);
  assert (error == 0);

  error = pthread_join(thPrint, NULL);
  assert (error == 0);

  error = pthread_join(thDemo, NULL);
  assert (error == 0);

  return error;
}

