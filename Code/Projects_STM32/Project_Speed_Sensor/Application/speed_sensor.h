/**
 * @file speed_sensor.h
 * @author Curtis Team
 * @brief Headers of application functions for speed sensors
 */
 
#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H

#include "car.h"
#include <stdint.h>

/**
 * @def SPEED_SENSOR_SAMPLES_USED 
 * @brief Number of samples used to compute speed. It is recommended to keep a value under 5 to keep a good fidelity of the variable. Musn't be negative.  
*/
#define SPEED_SENSOR_SAMPLES_USED 5

/**
 * @def SPEED_SENSOR_TIME_BETWEEN_TWO_UPDATES 
 * @brief Time corresponding to a hall sensor period : meaning time between two changes of speed 
*/
//#define SPEED_SENSOR_TIME_BETWEEN_TWO_UPDATES 100*1000 // µs
#define SPEED_SENSOR_TIME_BETWEEN_TWO_UPDATES 1000 // ms

/**
 * @def SPEED_xxxx 
 * @brief Used to get speed value in the adequate unit
 */
#define SPEED_MM_S		10						// millimeters per second
#define SPEED_CM_S 		1							// centimeters per second
#define SPEED_M__S		0.01 					// meters per second
#define SPEED_KM_S		0.00001				// kilometers per second
#define SPEED_KM_H		0.036					// kilometers per hour
#define SPEED_FT_S		0.0328084			// feet per second
#define SPEED_MI_H		0.02236936		// miles per hour
#define SPEED_MI_S		0.0000062137	// miles per second
#define SPEED_KNOT		0.01943845  	// knots

/**
 * @fn speed_sensor_init
 * @brief Initializes speed sensor 
*/
void speed_sensor_init(void);

/**
 * @fn speed_sensor_get
 * @brief Returns the value of speed : unit is given by unit parameter
 * @param unit -> float (a parameter to convert centimeters per second to any expected unit). It is recommended to use defined units such as SPEED_CM_S, SPEED_MM_S, SPEED_M_S, SPEED_KM_H, SPEED_FT_S,...
 * @param speed_identifier -> uint8_t : number of the speed sensor to examine
 * @return float (car speed : unit depends on parameter passed as argument) 
*/
float speed_sensor_get(float unit, uint8_t speed_identifier);

#endif //SPEED_SENSOR_H
