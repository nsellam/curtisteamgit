#include "position_sensor.h"

uint64_t current_position; 

// voir codes d'erreur
int position_sensor_init () {
	current_position = 0;
	return 0; 
}
