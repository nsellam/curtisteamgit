/**
 * @file API_main.c
 * @author Curtis Team
 * @brief Our main function that initializes the data structures and that starts all threads
 */

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stdio.h>
#include <assert.h>

/********************************/
/*       INCLUDES               */
/********************************/

#include <create_threads.h>
#include <data_interface.h>
#include <queue.h>

/********************************/
/*       DEFINES                */
/********************************/



/********************************/
/*       MAIN                   */
/********************************/



int main(void) {

  
  // create and start threads 
  // thread mirroring for communication PI-STM32
  // thread print for debug

  create();  // creates the commands fifo
  init_data();
  assert (create_threads() == 0);


  return 0;
}