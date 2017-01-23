/**
 * @file xpsapi.c
 * @author Curtis team
 * @brief service layer for the Raspberry Pi
 * Higher level functions
 */


/************************
 *      HEADERS         *
 ************************/
#include <xpsapi.h>
#include <data_interface.h>
#include <go_forward.h>
#include <create_threads.h>
#include <queue.h>

/************************
 *      INCLUDES        *
 ************************/
#include <stdio.h>
#include <pthread.h>


/************************
 *      VARIABLES       *
 ************************/



/************************
 *      FUNCTIONS       *
 ************************/


void goForward(float dist, uint16_t speed) {

   struct information I;  // to store the dist and speed values for the current function call into the commands fifo

// store the dist and speed values for the current function call into the commands fifo


if (dist > 0) {
  I.command_type = GO_FORWARD_COMMAND; 
  I.cmd1 = dist;
  I.cmd2 = (int)speed;
  I.cmd3 = 0;
  enq(I);
}

if (dist < 0) {//display();
  I.command_type = GO_BACKWARD_COMMAND; 
  I.cmd1 = dist;
  I.cmd2 = (int)speed;
  I.cmd3 = 0;
  enq(I);
}

  //display();

}