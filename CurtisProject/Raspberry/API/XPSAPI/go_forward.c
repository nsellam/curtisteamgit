/**
 * @file print.c
 * @author Curtis team
 * @brief application layer for the Raspberry Pi
 * to go forward for a given distance
 */




/************************
 *      LIBRARIES       *
 ************************/
#include <stdio.h>

/************************
 *      INCLUDES        *
 ************************/
#include <go_forward.h>
#include <waitPeriod.h>
#include <data_interface.h>
#include <hdmapi.h>
#include <xpsapi.h>
#include <queue.h>

#include <assert.h>

/************************
 *      DEFINES         *
 ************************/



/**
 * @def PERIOD_GO_FWD_NS
 * @brief the period of thread goForward in nano seconds
 */
#define PERIOD_GO_FWD_NS 10000000     // 10ms

/************************
 *      VARIABLES       *
 ************************/


/**
 *@brief memorizes the expected distance to be travelled (cm)
 */
float remainingDistanceToTravel;

/**
 *@brief memorizes the expected speed during this distance (cm/s) - an absolute value
 */
uint16_t speed;

/**
 *@brief memorizes the initial distance at the time the function goFwd is called by the user (cm)
 */
float initialDistance;

/**
* @brief memorizes if the thread is currently having an action on the car speed (Backward action)
*/
uint8_t goFwdActive;

/**
* @brief memorizes if the thread is currently having an action on the car speed (Backward action)
*/
uint8_t goBwdActive;


/**
 *@brief memorizes distance already traveled by the car when we enter the function goForward (cm)
 */
float initDist;

/**
 *@brief memorizes if the car go forward (FWD) or backward (BWD)
 */
int8_t carDirection;

/********************************/
/*       FUNCTIONS              */
/********************************/

/********************************/
/*       TH_PRINT               */
/********************************/



void* thread_goForward(void* arg) {

  //goFwdActive = 0; // memorizes if the function goForward of XPSAPI has been called or not

  struct information command; // the command comming from the fifo
	
  // set reference for 1st period
  clock_gettime(CLOCK_REALTIME, &T1_GoFwd); 

  // memorize the value of the distance at each time we enter the while below
  float traveledDistanceSoFar = 0.0;

  // initial values for goFwdSpeed and remainingDistanceToTravel
  remainingDistanceToTravel = 0;
  speed = 0;  


  // periodic task
  while (1) {  

    // ensure the period is respected
    waitPeriod (PERIOD_GO_FWD_NS, &T1_GoFwd, &T2_GoFwd);

    // update reference time for next call (T1_GoFwd)   -   THIS LINE ADDS IMPERFECTION TO THE LOOP
    clock_gettime(CLOCK_REALTIME, &T1_GoFwd);  

// THREAD CORE

      // is FIFO empty?
      if (empty()) {
        carDirection = STOP;
      }
      else {
// Interpret command type
         command = frontelement();
         if (command.command_type == GO_FORWARD_COMMAND) { 
            carDirection = FWD;
         }
         else if (command.command_type == GO_BACKWARD_COMMAND) { 
           carDirection = BWD;
         }
         else {
            carDirection = STOP;
         }
      } 




// Go FWD
      if (carDirection == FWD) { 
         if ((remainingDistanceToTravel <= 0) && (goFwdActive == 0)) {     // no distance to travel available yet
            initDist = get_travelled_distance_R();
            remainingDistanceToTravel = command.cmd1;
            speed = command.cmd2;
         } 

         if ((remainingDistanceToTravel <= 0) && (goFwdActive == 1)) {    // distance has just been traveled
            set_motor_speed(0);
            remainingDistanceToTravel = 0;
            goFwdActive = 0;
            deq(); // dequeue the current command from FIFO
            display();
         }  

         if (remainingDistanceToTravel > 0) {          printf("%f\n",remainingDistanceToTravel);                // distance has not been entierely travelled yet
            set_motor_speed(speed);
            traveledDistanceSoFar = get_travelled_distance_R();
            remainingDistanceToTravel -= (traveledDistanceSoFar - initDist);
            initDist = traveledDistanceSoFar;
            goFwdActive = 1;
         } 
     }



// Go BWD
      if (carDirection == BWD) {
         if ((remainingDistanceToTravel >= 0) && (goBwdActive == 0)) {     // no distance to travel available yet
            initDist = get_travelled_distance_R();
            remainingDistanceToTravel = command.cmd1;
            speed = command.cmd2;
         } 

         if ((remainingDistanceToTravel >= 0) && (goBwdActive == 1)) {     // distance has just been traveled
            set_motor_speed(0);
            remainingDistanceToTravel = 0;
            goBwdActive = 0;
            deq(); // dequeue the current command from FIFO
            display();
         }  

         if (remainingDistanceToTravel < 0) {     printf("%f\n",remainingDistanceToTravel);                     // distance has not been entierely travelled yet
            set_motor_speed(-speed);
            traveledDistanceSoFar = get_travelled_distance_R();
            remainingDistanceToTravel -= (traveledDistanceSoFar - initDist);
            initDist = traveledDistanceSoFar;
            goBwdActive = 1;
         } 
     }

  }
}

