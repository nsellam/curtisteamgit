/**
 * @file speed_sensor.c
 * @author Curtis Team
 * @brief Application functions for speed sensors
 */
 
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
 * @brief Last computed speed (expressed in centimeters per second) for each speed sensor
*/
float speed[HALL_SENSOR_NUMBER]; // cm/s

/**
 * @fn speed_sensor_compute
 * @param speed_identifier -> uint8_t : Number of the speed sensor to consider
 * @brief Computes speed and stores the result in a private variable 
*/
void speed_sensor_compute(uint8_t hall_identifier);

void speed_sensor_init() {
	int i = 0; 
	for (i=0; i <HALL_SENSOR_NUMBER; i++) speed[i] = 0.0; 
	
	if (SPEED_SENSOR_SAMPLES_USED <= HALL_SENSOR_MAX_SAVED_POP) {
		SAMPLE_TO_USE  = SPEED_SENSOR_SAMPLES_USED - 1;
	}
	else {
		SAMPLE_TO_USE  = HALL_SENSOR_MAX_SAVED_POP - 1;
	}
}

void speed_sensor_compute(uint8_t speed_identifier) {
	uint64_t tf = micros();
	uint64_t t0 = hall_sensor_get_last_pop(SAMPLE_TO_USE, speed_identifier);
	
	if (t0 == 0) {
		speed[speed_identifier] = 0; // Car hasn't move yet
	} 
	else if (t0 != tf) { 
		speed[speed_identifier] = (float) (DELTA_DISTANCE * (SAMPLE_TO_USE + 1) / ((float)(tf - t0)/((float)SYSTICK_FREQ)));
	}
	else {
		speed[speed_identifier] = INFINITE; // Car browses instantly the distance
	} 
}

float speed_sensor_get(float unit, uint8_t speed_identifier) {
	speed_sensor_compute(speed_identifier);
	return speed[speed_identifier] * unit;
}
