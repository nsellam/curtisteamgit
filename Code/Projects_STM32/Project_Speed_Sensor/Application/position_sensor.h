/**
 * @file position_sensor.h
 * @author Curtis Team
 * @brief Headers of application functions for position sensors
 */

#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include <stdint.h>
#include "car.h"

/**
 * @def POSITION_xx
 * @brief Used to get position value in the adequate unit 
 */
#define POSITION_MM		10					// millimeters
#define POSITION_CM		1						// centimeters
#define POSITION_M_		0.01				// meters
#define	POSITION_KM		0.00001			// kilometers
#define POSITION_IN		0.393701		// inches
#define POSITION_FT		0.0328084		// feet

/**
 * @fn position_sensor_init
 * @brief Initializes position sensor 
*/
void position_sensor_init (void);

/**
 * @fn position_sensor_get
 * @brief Returns the value of position : unit is given by unit parameter
 * @param unit -> float (a parameter to convert centimeters to any expected unit). It is recommended to use defined units such as POSITION_MM, POSITION_CM, POSITION_M, POSITION_IN, POSITION_FT,...
 * @return float (car position : unit depends on parameter passed as argument) 
*/
float position_sensor_get (float unit);

/**
 * @fn position_sensor_compute
 * @brief Computes position and stores the result in a private variable 
*/
void position_sensor_compute (void);

#endif //POSITION_SENSOR_H
