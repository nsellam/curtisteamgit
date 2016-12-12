#include "callbacks_services.h"
#include "hall_sensor.h"
#include "systick.h"

void callbacks_services_exti(uint32_t EXTI_Line) {
	if (EXTI_Line == HALL_SENSOR_LINE) {
		hall_sensor_callback();
	}
}

