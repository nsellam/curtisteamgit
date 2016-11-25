#include <stdint.h>
#include "stm32f10x.h"
#include "systick.h"
#include "hall_sensor.h"
#include "position_sensor.h"
#include "speed_sensor.h"


// for test only
float jeanmichelposition;
float jeanmichelvitesse;



int main(void) {
	systick_init ();
	hall_sensor_init();
	
	// for test only 
	
	position_sensor_init();
	speed_sensor_init();
	
	while(1) {
		position_sensor_compute();
		jeanmichelposition = position_sensor_get();
		
		speed_sensor_compute();
		jeanmichelvitesse = speed_sensor_get(KM_H);
	}

  return 0;
}
