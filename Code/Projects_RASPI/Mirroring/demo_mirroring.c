/**
 * @file demo_mirroring.c
 * @author Curtis team
 * @brief asks user for settings (motors) 
 * to print any shared variables
 */




/************************
 *      LIBRARIES       *
 ************************/
#include <stdio.h>

/************************
 *      INCLUDES        *
 ************************/
#include <demo_mirroring.h>
#include <waitPeriod.h>
#include <data.h>

/************************
 *      DEFINES         *
 ************************/



/**
 * @def PERIOD_DEMO_NS
 * @brief the period of thread print in nano seconds
 */
#define PERIOD_DEMO_NS 1000000000     // 1s

/************************
 *      VARIABLES       *
 ************************/
  uint8_t motor_speed ;

/********************************/
/*       FUNCTIONS              */
/********************************/



/********************************/
/*       TH_DEMO_MIRRORING      */
/********************************/

//TODO

void* demo_mirroring(void* arg) {

  // set reference for 1st period
  clock_gettime(CLOCK_REALTIME, &T1_demo); 
  
  // periodic task
  while (1) {

    // ensure the period is respected
    waitPeriod (PERIOD_DEMO_NS, &T1_demo, &T2_demo);

    // update reference time for next call (T1_demo)   -   THIS LINE ADDS IMPERFECTION TO THE LOOP
    clock_gettime(CLOCK_REALTIME, &T1_demo);  

    // demo

  // ask the user for a motor speed value and update it in the structure to be mirrored


  printf("												Please enter a motor speed\n");
  printf("													- 0 means max backward speed\n");
  printf("													- 127 means stop the motor\n");
  printf("													- 255 means max forward speed\n");

  scanf("%i", &motor_speed);


  set_motor_speed_data(motor_speed); 

  }
}

