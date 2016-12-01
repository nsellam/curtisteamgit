#include "hall_sensor.h"
#include "systick.h"
#include "exti.h"

/**
 * @var hall_sensor_number_of_pop
 * @brief 
*/
uint32_t hall_sensor_number_of_pop;

/**
 * @var hall_sensor_last_pops
 * @brief 
*/
uint64_t hall_sensor_last_pops[HALL_SENSOR_MAX_SAVED_POP];

/**
 * @var hall_sensor_sector
 * @brief 
*/
uint16_t hall_sensor_sector;

/**
 * @var hall_sensor_lap
 * @brief 
*/
uint32_t hall_sensor_lap;

/**
 * @fn hall_sensor_reset
 * @brief 
 * @param 
 * @return 
 * @retval 
*/
void hall_sensor_reset (void);

void hall_sensor_init(void) {
	hall_sensor_reset(); 
	EXTI_QuickInit(HALL_SENSOR_GPIO, HALL_SENSOR_PIN, HALL_SENSOR_TRIGG, HALL_SENSOR_PRIO);
}

void hall_sensor_callback (void) {

	hall_sensor_last_pops[hall_sensor_number_of_pop] = micros();
	
	hall_sensor_number_of_pop ++;
	if (hall_sensor_number_of_pop >= HALL_SENSOR_MAX_SAVED_POP) hall_sensor_number_of_pop = 0; else {} 
	
	hall_sensor_sector ++;
	if (hall_sensor_sector >= HALL_SENSOR_NUMBER_OF_SECTORS) 
	{
		hall_sensor_sector = 0; 
		hall_sensor_lap ++;
	}
}

/**
 * @fn hall_sensor_reset
 * @brief Reset all the variables used to describe a hall_sensor
*/
void hall_sensor_reset (void) {
	int i = 0;
	hall_sensor_number_of_pop = 0;
	hall_sensor_sector = 0;
	hall_sensor_lap = 0;
	for (i = 0; i < HALL_SENSOR_MAX_SAVED_POP; i++)	{
		hall_sensor_last_pops[i] = 0;
	}
}

uint16_t hall_sensor_get_sector (void){
	if (hall_sensor_sector >= HALL_SENSOR_NUMBER_OF_SECTORS) return ERROR_SENSOR_OUT_OF_RANGE; else {};
	return hall_sensor_sector;
}

uint32_t hall_sensor_get_lap(void) {
	// no test can be done to validate lap number 
	return hall_sensor_lap;
}

uint64_t get_hall_sensor_last_pop (uint8_t n) {
	int position_to_read = hall_sensor_number_of_pop - n;
	
	if (n > HALL_SENSOR_MAX_SAVED_POP) return ERROR_VALUE_NOT_FOUND;  else {}; 

	if (position_to_read < 0) position_to_read = position_to_read + HALL_SENSOR_MAX_SAVED_POP; // TODO : verifier ce calcul et le commenter
		
	return hall_sensor_last_pops[position_to_read];
}
