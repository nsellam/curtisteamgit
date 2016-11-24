#include "speed_sensor.h"

float speed;

void speed_sensor_compute() {
	speed = 42.0;
}

float speed_sensor_get_speed(void) {
	return speed;
}
