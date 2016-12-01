/**
 * @file uncompress.c
 * @author Curtis Team
 * @brief Functions to uncompress received data 
 */
 
#include "uncompress.h"
#include "compress.h"
#include "car.h"

/**
 * @def SPEED_POSITIVE_RESCALER
 * @brief Coefficient to uncompress positive speeds 
*/
#define SPEED_POSITIVE_RESCALER (float)(CAR_MAX_SPEED/COMPRESSED_SPEED_MAX)

/**
 * @def SPEED_NEGATIVE_RESCALER 
 * @brief Coefficient to uncompress negative speeds 
*/
#define SPEED_NEGATIVE_RESCALER (float)(CAR_MIN_SPEED/COMPRESSED_SPEED_MIN)


float uncompress_speed (int16_t speed, float unit) {
	float uncompressed = 0.0; 
	
	if (speed == 0) {
		uncompressed = CAR_ZERO_SPEED; 
	}
	else if (speed > 0) {
		uncompressed = (float) (speed * SPEED_POSITIVE_RESCALER ); 
	}
	else {
		uncompressed = (float) (speed * SPEED_NEGATIVE_RESCALER);
	}
	
	return uncompressed * unit;
}

float uncompress_position (uint8_t position, float unit) {
	float uncompressed = 0.0; 
	
	return uncompressed;
}
