/**
 * @file compress.c
 * @author Curtis Team
 * @brief Functions to compress data for sending 
 */
 
#include "stm32f10x.h"
#include "position_sensor.h"
#include "speed_sensor.h"
#include "compress.h"

/**
 * @def SPEED_POSITIVE_RESCALER
 * @brief Coefficient to compress positive speeds 
*/
#define SPEED_POSITIVE_RESCALER (COMPRESSED_SPEED_MAX - COMPRESSED_SPEED_ZERO) / ((CAR_MAX_SPEED - CAR_ZERO_SPEED) * SPEED_UNIT)

/**
 * @def SPEED_NEGATIVE_RESCALER 
 * @brief Coefficient to compress negative speeds 
*/
#define SPEED_NEGATIVE_RESCALER (COMPRESSED_SPEED_MIN - COMPRESSED_SPEED_ZERO) / ((CAR_ZERO_SPEED - CAR_MIN_SPEED) * SPEED_UNIT)

/**
 * @def POSITION_POSITIVE_RESCALER
 * @brief Coefficient to compress positive positions 
*/
#define POSITION_POSITIVE_RESCALER (COMPRESSED_POSITION_MAX - COMPRESSED_POSITION_ZERO) / ((CAR_MAX_POSITION - CAR_ZERO_POSITION) * POSITION_UNIT)

/**
 * @def POSITION_NEGATIVE_RESCALER 
 * @brief Coefficient to compress negative positions 
*/
#define POSITION_NEGATIVE_RESCALER (COMPRESSED_POSITION_MIN - COMPRESSED_POSITION_ZERO) / ((CAR_ZERO_POSITION - CAR_MIN_POSITION) * POSITION_UNIT)

/**
 * @def SPEED_UNIT
 * @brief To facilitate calculations understanding, all speeds are first convert in a given unit. This parameter is essential but has no effect on the result. 
*/
#define SPEED_UNIT				SPEED_KM_H

/**
 * @def POSITION_UNIT
 * @brief To facilitate calculations understanding, all positions are first convert in a given unit. This parameter is essential but has no effect on the result. 
*/
#define POSITION_UNIT			POSITION_M_


int16_t compress_speed (float speed, float unit) {
	
	float speed_kmh = (speed/unit) * SPEED_UNIT; // conversion to kilometers per hour
	int16_t compressed = COMPRESSED_SPEED_ZERO; 
	
	if (speed_kmh > (CAR_MAX_SPEED * SPEED_UNIT)) {
		compressed = COMPRESSED_SPEED_MAX; 
	}
  else if (speed_kmh < (CAR_MIN_SPEED)* SPEED_UNIT) {
		compressed = COMPRESSED_SPEED_MIN;
	}
	else if (speed_kmh < CAR_ZERO_SPEED * SPEED_UNIT) {
		compressed = COMPRESSED_SPEED_ZERO - (int16_t) (speed_kmh * SPEED_NEGATIVE_RESCALER);
	}
	else if (speed_kmh > CAR_ZERO_SPEED * SPEED_UNIT) {
		compressed = (int16_t) (speed_kmh * SPEED_POSITIVE_RESCALER) + COMPRESSED_SPEED_ZERO;
	}
	else {}
		
	return compressed;
}

uint8_t compress_position (float position, float unit) {

	float position_m = (position/unit) * POSITION_UNIT; // conversion to meters
	uint8_t compressed = COMPRESSED_POSITION_ZERO; 
	
	if (position_m > (CAR_MAX_POSITION * POSITION_UNIT)) {
		compressed = COMPRESSED_POSITION_MAX; 
	}
  else if (position_m < (CAR_MIN_POSITION)* POSITION_UNIT) {
		compressed = COMPRESSED_POSITION_MIN;
	}
	else if (position_m < CAR_ZERO_POSITION * POSITION_UNIT) {
		compressed = COMPRESSED_POSITION_ZERO - (uint8_t) (position_m * POSITION_NEGATIVE_RESCALER);
	}
	else if (position_m > CAR_ZERO_POSITION * POSITION_UNIT) {
		compressed = (uint8_t) (position_m * POSITION_POSITIVE_RESCALER) + COMPRESSED_POSITION_ZERO;
	}
	else {}
		
	return compressed;
}
