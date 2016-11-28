/**
 * @file demoMirroring.c
 * @author Curtis Team
 * @brief Demo for the mirroring thread running on Raspberry Pi
 * Synchronizes actuators and sensors
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
#include <hdmapi.h>

/********************************/
/*       DEFINES                */
/********************************/

#define PRIO_MIRRORING 30
#define PRIO_PRINT 4



/********************************/
/*       MAIN                   */
/********************************/



int main(void) {

  
  // create and start threads 
  // thread mirroring for communication PI-STM32
  // thread print for debug
  assert (create_threads() == 0);

  return 0;
}