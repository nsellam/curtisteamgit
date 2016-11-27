#include "speed_sensor.h"
#include "hall_sensor.h"
#include "systick.h"

/**
 * @def DELTA_DISTANCE 
 * @brief Travelled distance between two samples
*/
#define DELTA_DISTANCE 	(float) PI*((float)(((float)CAR_WHEEL_SIZE/(float)HALL_SENSOR_NUMBER_OF_SECTORS)))

/**
 * @def INFINITE 
 * @brief Value given if car browses instantly the distance between two samples
*/
#define INFINITE 9999.99

/**
 * @var SAMPLE_TO_USE 
 * @brief Number of the sample to consider to compute speed
*/
uint8_t SAMPLE_TO_USE;

/**
 * @var speed 
 * @brief Last computed speed (expressed in centimeters per second)
*/
float speed = 0; // cm/s

void speed_sensor_init() {
	
	speed = 0; 
	
	if (SPEED_SENSOR_SAMPLES_USED <= HALL_SENSOR_MAX_SAVED_POP) {
		SAMPLE_TO_USE  = SPEED_SENSOR_SAMPLES_USED - 1;
	}
	else {
		SAMPLE_TO_USE  = HALL_SENSOR_MAX_SAVED_POP - 1;
	}
}

void speed_sensor_compute() {
	uint64_t tf = micros();
	uint64_t t0 = get_hall_sensor_last_pop(SAMPLE_TO_USE);
	
	if (t0 == 0) {speed = 0;} // Car hasn't move yet
	else if (t0 != tf) { speed = (float) (DELTA_DISTANCE * (SAMPLE_TO_USE + 1) / ((float)(tf - t0)/((float)SYSTICK_FREQ)));}
	else {speed = INFINITE;} // Car browses instantly the distance
}

float speed_sensor_get(float unit) {
	return speed * unit;
}
