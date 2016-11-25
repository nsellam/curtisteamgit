#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H

#include "car.h"

#define SPEED_SENSOR_SAMPLES_USED 3

#define MM_S		10						// millimeters per second
#define CM_S 		1							// centimeters per second
#define M_S			0.01 					// meters per second
#define KM_S		0.00001				// kilometers per second
#define KM_H		0.036					// kilometers per hour
#define FT_S		0.0328084			// feet per second
#define MI_H		0.02236936		// miles per hour
#define MI_S		0.0000062137	// miles per second
#define KNOT		0.01943845  	// knots



float speed_sensor_get(float unit);

void speed_sensor_compute(void);

void speed_sensor_init(void);

#endif //SPEED_SENSOR_H
