/**
 * @file callbacks_services.c
 * @author Curtis Team
 * @brief Callbacks functions
 */

#include "callbacks_services.h"
#include "hall_sensor.h"
#include "speed_sensor.h"
#include "systick.h"

/**
 * @var remaining_time_to_hall_period 
 * @brief Number of systick iteruptions to wait until next hall sensor period
*/
uint32_t remaining_time_to_hall_period = SPEED_SENSOR_TIME_BETWEEN_TWO_UPDATES; 

void callbacks_services_exti(uint32_t EXTI_Line) {
	if (EXTI_Line == HALL_SENSOR_L_LINE) {
		hall_sensor_callback(HALL_IDENTIFIER_L);
	}
	else if (EXTI_Line == HALL_SENSOR_R_LINE) {
		hall_sensor_callback(HALL_IDENTIFIER_R);
	}
}

void callbacks_services_hall_period (void) {
	remaining_time_to_hall_period --; 
	if (remaining_time_to_hall_period == 0) {
		hall_sensor_count_peridod_ticks();
		callbacks_services_reset_time_to_next_hall_period();
	}
}

void callbacks_services_reset_time_to_next_hall_period (void) {
	remaining_time_to_hall_period = SPEED_SENSOR_TIME_BETWEEN_TWO_UPDATES; 
}
