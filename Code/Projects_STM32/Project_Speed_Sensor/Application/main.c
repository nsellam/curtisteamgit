#include <stdint.h>
#include "systick.h"
#include "hall_sensor.h"
#include "position_sensor.h"
#include "speed_sensor.h"
#include "compress.h"
#include "data.h"

 


// for test only
float jeanmichelposition;
float jeanmichelvitesse;



int main(void) {
//	
//	

	//////// TESTING \\\\\\\\
	
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t e = 0;
	uint8_t f = 0;
	uint8_t g = 0;
	uint8_t h = 0;
	uint8_t i = 0;

//	a = compress_position (0.0, POSITION_CM); 		// 0								=> 0x80 -> OK
//	b = compress_position (1.0, POSITION_KM); 		// hors range +			=> 0xFF -> OK
//	c = compress_position (-250.0, POSITION_M_); 	// hors range -			=> 0x00 -> OK
//	d = compress_position (500.5, POSITION_CM); 	// in range + 			=> 0x86 -> OK
//	e = compress_position (85.4, POSITION_M_); 		// in range + 			=> 0xEB -> OK
//	f = compress_position (100.0, POSITION_M_); 	// in range +				=> 0xFF -> OK
//	g = compress_position (-500.5, POSITION_CM); 	// in range -				=> 0x7A -> OK
//	h = compress_position (-85.4, POSITION_M_); 	// in range -				=> 0x13 -> OK
//	i = compress_position (-100.0, POSITION_M_); 	// in range -				=> 0x00 -> OK
//	
	a = compress_speed (0.0, SPEED_CM_S); 				// 0								=> 0
	b = compress_speed (10.0, SPEED_KM_H); 				// hors range +			=> 32767
	c = compress_speed (-10.0, SPEED_KM_H); 			// hors range -			=> -32767
	d = compress_speed (17.7, SPEED_CM_S); 				// in range +		 		=> 
	e = compress_speed (97.22, SPEED_CM_S); 			// in range + 			=> 
	f = compress_speed (5.0, SPEED_KM_H); 				// in range +				=> 
	g = compress_speed (-17.7, SPEED_CM_S); 			// in range -				=> 
	h = compress_speed (-97.22, SPEED_CM_S); 			// in range -				=> 
	i = compress_speed (-5.0, SPEED_KM_H); 				// in range -				=> 
	
	a = a+b+c+d+e+f+g+h+i; // sinon ce boulet me met des warnings
	
	
	
	systick_init();
	hall_sensor_init();
	position_sensor_init();
	speed_sensor_init();

	while(1) {
		position_sensor_compute();
		jeanmichelposition = position_sensor_get(POSITION_CM);
		pData_STM->travelled_distance = jeanmichelposition;
		
		speed_sensor_compute();
		jeanmichelvitesse = speed_sensor_get(SPEED_CM_S);
		pData_STM->car_speed = jeanmichelvitesse;
	}

  return 0;
}
