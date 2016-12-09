/**
 * @file hall_sensor.c
 * @author Curtis Team
 * @brief Service functions for hall sensors
 */

#include "hall_sensor.h"
#include "callbacks_services.h"
#include "car.h"
#include "systick.h"
#include "exti.h"

/**
 * @def FW_ADDER 
 * @brief Value to be add to variables at each front when car go forward. 
*/
#define FW_ADDER 1 

/**
 * @def FW_ADDER 
 * @brief Value to be add to variables at each front when car go backward. 
*/
#define BW_ADDER -1

/**
 * @var hall_sensor_number_of_pop
 * @brief Number of the hall detection. Positive is counted on rising edges, negative if not.  
*/
int32_t hall_sensor_number_of_pop[HALL_SENSOR_NUMBER];

/**
 * @var hall_sensor_last_pops
 * @brief Date of the last dectections of each hall sensor
*/
uint64_t hall_sensor_last_pops[HALL_SENSOR_MAX_SAVED_POP][HALL_SENSOR_NUMBER];

/**
 * @var hall_sensor_sector
 * @brief Number of the sector currently seen by each hall sensor
*/
uint16_t hall_sensor_sector[HALL_SENSOR_NUMBER];

/**
 * @var hall_sensor_lap
 * @brief Number of laps count by each hall sensor. Positive is counted on rising edges, negative if not. 
*/
int32_t hall_sensor_lap[HALL_SENSOR_NUMBER];

/**
 * @var hall_sensor_periode_ticks
 * @brief Number of ticks count during this periode
*/
int8_t hall_sensor_current_periode_ticks[HALL_SENSOR_NUMBER];

/**
 * @var hall_sensor_periode_ticks
 * @brief Number of ticks count during the last periode
*/
int8_t hall_sensor_periode_ticks[HALL_SENSOR_NUMBER];

/**
 * @fn hall_sensor_reset
 * @brief Reset the values kept in hall sensor variables
 * @param hall_identifier -> uint8_t : hall sensor to consider
*/
void hall_sensor_reset (uint8_t hall_identifier);

/**
 * @fn hall_sensor_update
 * @brief Update the hall sensor definied variables according to adder given 
 * @param hall_identifier -> uint8_t : hall sensor to consider
 * @param adder -> int8_t (Increment to put on the variables. Must be FW_ADDER or BW_ADDER)
*/
void hall_sensor_update(uint8_t hall_identifier, int8_t adder);

void hall_sensor_start(uint8_t hall_identifier, uint8_t direction) {
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	EXTITrigger_TypeDef trigg;
	
	if (hall_identifier == HALL_IDENTIFIER_L) {
		GPIO = HALL_SENSOR_L_GPIO;
		pin = HALL_SENSOR_L_PIN;
	}
	else if (hall_identifier == HALL_IDENTIFIER_R) {
		GPIO = HALL_SENSOR_R_GPIO;
		pin = HALL_SENSOR_R_PIN;
	}
	else {return;}	
	
	if (direction == CAR_FW_DIRECTION) {
		trigg = HALL_SENSOR_TRIGG_FW;
	}
	else {
		trigg = HALL_SENSOR_TRIGG_BW;
	}
	
	EXTI_QuickInit(GPIO, pin, trigg, HALL_SENSOR_PRIO);
}

void hall_sensor_init(uint8_t hall_identifier, uint8_t direction) {
	hall_sensor_reset(hall_identifier);
	hall_sensor_start(hall_identifier, direction);
}

void hall_sensor_update(uint8_t hall_identifier, int8_t adder) {
	hall_sensor_last_pops[hall_sensor_number_of_pop[hall_identifier]][hall_identifier] = millis();
	
	hall_sensor_number_of_pop[hall_identifier] ++;
	if (hall_sensor_number_of_pop[hall_identifier] >= HALL_SENSOR_MAX_SAVED_POP) hall_sensor_number_of_pop[hall_identifier] = 0; else {} 
	
	hall_sensor_sector[hall_identifier] = hall_sensor_sector[hall_identifier] + adder;
	
	if (hall_sensor_sector[hall_identifier] == (uint16_t)(-1)) {
		hall_sensor_sector[hall_identifier] = HALL_SENSOR_NUMBER_OF_SECTORS - 1; 
		hall_sensor_lap[hall_identifier] --;
	}
	
	else if (hall_sensor_sector[hall_identifier] >= HALL_SENSOR_NUMBER_OF_SECTORS) {
		hall_sensor_sector[hall_identifier] = 0; 
		hall_sensor_lap[hall_identifier] ++;
	}
	else {}
	hall_sensor_current_periode_ticks[hall_identifier] = hall_sensor_current_periode_ticks[hall_identifier] + adder;
}

void hall_sensor_callback (uint8_t hall_identifier) {
	
	if (car_direction_get() == CAR_FW_DIRECTION) {
		hall_sensor_update(hall_identifier, FW_ADDER);
	}
	else {
		hall_sensor_update(hall_identifier, BW_ADDER);
	}
}

/**
 * @fn hall_sensor_reset
 * @brief Reset all the variables used to describe a hall_sensor
*/
void hall_sensor_reset (uint8_t hall_identifier) {
	int i = 0;
	hall_sensor_number_of_pop[hall_identifier] = 0;
	hall_sensor_sector[hall_identifier] = 0;
	hall_sensor_lap[hall_identifier] = 0;
	for (i = 0; i < HALL_SENSOR_MAX_SAVED_POP; i++)	{
		hall_sensor_last_pops[i][hall_identifier] = 0;
	}
	hall_sensor_periode_ticks[hall_identifier] = 0;
	hall_sensor_current_periode_ticks[hall_identifier] = 0;
	callbacks_services_reset_time_to_next_hall_period();
}

uint16_t hall_sensor_get_sector (uint8_t hall_identifier){
	if (hall_sensor_sector[hall_identifier] >= HALL_SENSOR_NUMBER_OF_SECTORS) return ERROR_SENSOR_OUT_OF_RANGE; else {};
	return hall_sensor_sector[hall_identifier];
}

int32_t hall_sensor_get_lap(uint8_t hall_identifier) {
	// no test can be done to validate lap number 
	return hall_sensor_lap[hall_identifier];
}

uint64_t hall_sensor_get_last_pop (uint8_t n, uint8_t hall_identifier) {
	int position_to_read = hall_sensor_number_of_pop[hall_identifier] - n;
	
	if (n > HALL_SENSOR_MAX_SAVED_POP) return ERROR_VALUE_NOT_FOUND;  else {}; 

	if (position_to_read < 0) position_to_read = position_to_read + HALL_SENSOR_MAX_SAVED_POP; // TODO : verifier ce calcul et le commenter
		
	return hall_sensor_last_pops[position_to_read][hall_identifier];
}

void hall_sensor_count_peridod_ticks (void) {
	int i = 0; 
	for (i=0; i<HALL_SENSOR_NUMBER; i++) {
		hall_sensor_periode_ticks[i] = hall_sensor_current_periode_ticks[i];
		hall_sensor_current_periode_ticks[i] = 0;
	}
}

int8_t hall_sensor_get_number_ticks_in_period (uint8_t hall_identifier) {
	return hall_sensor_periode_ticks[hall_identifier];
}
