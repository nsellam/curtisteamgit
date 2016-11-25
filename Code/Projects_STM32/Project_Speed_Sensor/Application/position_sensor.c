#include "position_sensor.h"
#include "hall_sensor.h"

float current_position; 

void position_sensor_init (void) {
	current_position = 0;
}

float position_sensor_get (void) {
	return current_position;
}

void position_sensor_compute (void) {
	float lap = (float) hall_sensor_get_lap();
	float sector = (float) hall_sensor_get_sector();
	current_position = PI * CAR_WHEEL_SIZE * (lap +  sector / HALL_SENSOR_NUMBER_OF_SECTORS);
}
