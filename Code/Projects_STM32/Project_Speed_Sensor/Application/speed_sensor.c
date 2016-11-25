#include "speed_sensor.h"
#include "hall_sensor.h"
#include "systick.h"


#define DELTA_DISTANCE 	(float) PI*((float)(((float)CAR_WHEEL_SIZE/(float)HALL_SENSOR_NUMBER_OF_SECTORS)))

#define INFINITE 9999.99

uint8_t SAMPLES_TO_USE;
float speed = 0; // cm/s

void speed_sensor_init() {
	
	speed = 0; 
	
	if (SPEED_SENSOR_SAMPLES_USED <= HALL_SENSOR_MAX_SAVED_POP) {
		SAMPLES_TO_USE  = SPEED_SENSOR_SAMPLES_USED;
	}
	else {
		SAMPLES_TO_USE  = HALL_SENSOR_MAX_SAVED_POP;
	}
}

void speed_sensor_compute() {
	uint64_t tf = micros();
	uint64_t t0 = get_hall_sensor_last_pop(SAMPLES_TO_USE);
	
	if (t0 == 0) {speed = 0;} // Car hasn't move yet
	else if (t0 != tf) { speed = (float) (DELTA_DISTANCE * SAMPLES_TO_USE) / ((float)(tf - t0)/((float)SYSTICK_FREQ));}
	else {speed = INFINITE;} // Car browses instantly the distance
}

float speed_sensor_get(float unit) {
	return speed * unit;
}
