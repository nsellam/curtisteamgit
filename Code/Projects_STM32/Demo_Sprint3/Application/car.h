/**
 * @file car.h
 * @author Curtis Team
 * @brief Headers of functions to describe the car 
 */

#include <stm32f10x.h>

#ifndef CAR_H
#define CAR_H

#define CAR_WHEEL_SIZE 		19									// cm

#define CAR_MAX_SPEED 		138.889							// cm/s  => 138.889 cm/s = 5 km/h
#define CAR_MIN_SPEED			-CAR_MAX_SPEED			// cm/s
#define CAR_ZERO_SPEED		0.0										// cm/s

#define CAR_MAX_POSITION	10000.0							// cm
#define CAR_MIN_POSITION	-CAR_MAX_POSITION		// cm
#define CAR_ZERO_POSITION	0										// cm

#define	CAR_MESSAGE_LENGTH 8 // bits

#define PI 3.14159265359







/////// A METTRE DANS MOTOR.H ?????????

#define CAR_FW_DIRECTION 0 // forward
#define CAR_BW_DIRECTION 1 // backward 

/**
 * @fn car_direction_set
 * @param direction -> uint8_t (new direction to set to car direction variable. Must be CAR_FW_DIRECTION or CAR_BW_DIRECTION)
 * @brief Change the variable describing car direction
*/
void car_direction_set (uint8_t direction);

/**
 * @fn car_direction_set
 * @brief Change the variable describing car direction
 * @return uint8_t (car direction : CAR_FW_DIRECTION or CAR_BW_DIRECTION) 
*/
uint8_t car_direction_get (void);
#endif //CAR_H
