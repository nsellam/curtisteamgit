/**
 * @file xpsapi.h
 * @author Curtis Team
 * @brief header of xpsapi.c
 */

#ifndef XPSAPI_H
#define XPSAPI_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>


/********************************/
/*       DEFINES                */
/********************************/



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
* @brief tells the car to go forard for a certain distance (at a certain speed)
* @param the distance to travel (cm)
* @param the car speed for this distance to travel (cm/s)
* @retval none
*/

void goForward(float expedtedDistance, uint16_t speed);





#endif