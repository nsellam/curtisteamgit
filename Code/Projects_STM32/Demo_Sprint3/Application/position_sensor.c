/**
 * @file position_sensor.h
 * @author Curtis Team
 * @brief Application functions for position sensors
 */

#include "position_sensor.h"
#include "hall_sensor.h"

/**
 * @var speed 
 * @brief Last computed position (expressed in centimeters) for each hall sensor
*/
float position[HALL_SENSOR_NUMBER]; 

/**
 * @fn position_sensor_compute
 * @param position_identifier -> uint8_t : Number of the position sensor to consider
 * @brief Computes position and stores the result in a private variable 
*/
void position_sensor_compute (uint8_t position_identifier);

void position_sensor_init (void) {
	int i = 0;
	for (i=0; i <HALL_SENSOR_NUMBER; i++) position[i] = 0.0;
}

void position_sensor_compute (uint8_t position_identifier) {
	float lap = (float) hall_sensor_get_lap(position_identifier);
	float sector = (float) hall_sensor_get_sector(position_identifier);
	position[position_identifier] = PI * CAR_WHEEL_SIZE * (lap +  sector / HALL_SENSOR_NUMBER_OF_SECTORS);
}

float position_sensor_get (float unit, uint8_t position_identifier) {
	position_sensor_compute(position_identifier);
	return position[position_identifier] * unit;
}
