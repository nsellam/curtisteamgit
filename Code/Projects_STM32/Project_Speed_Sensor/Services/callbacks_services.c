/**
 * @file callbacks_services.c
 * @author Curtis Team
 * @brief Callbacks functions
 */

#include "callbacks_services.h"
#include "hall_sensor.h"
#include "systick.h"

void callbacks_services_exti(uint32_t EXTI_Line) {
	if (EXTI_Line == HALL_SENSOR_L_LINE) {
		hall_sensor_callback(HALL_IDENTIFIER_L);
	}
	else if (EXTI_Line == HALL_SENSOR_R_LINE) {
		hall_sensor_callback(HALL_IDENTIFIER_R);
	}
}

