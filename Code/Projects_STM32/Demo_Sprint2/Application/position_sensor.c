#include "position_sensor.h"
#include "hall_sensor.h"

/**
 * @var speed 
 * @brief Last computed position (expressed in centimeters)
*/
float position; 

void position_sensor_init (void) {
	position = 0;
}

void position_sensor_compute (void) {
	float lap = (float) hall_sensor_get_lap();
	float sector = (float) hall_sensor_get_sector();
	position = PI * CAR_WHEEL_SIZE * (lap +  sector / HALL_SENSOR_NUMBER_OF_SECTORS);
}

float position_sensor_get (float unit) {
	return position * unit;
}
