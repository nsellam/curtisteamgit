#include <stdint.h>
#include "systick.h"
#include "hall_sensor.h"
#include "position_sensor.h"
#include "speed_sensor.h"
#include "compress.h"
#include "uncompress.h"
#include "data.h"

 


// for test only
float jeanmichelposition;
float jeanmichelvitesse;

float jeanraymondposition; 
float jeanraymondvitesse;



int main(void) {
//	
//	

	//////// TESTING \\\\\\\\
	
	int16_t a = 0;
	int16_t b = 0;
	int16_t c = 0;
	int16_t d = 0;
	int16_t e = 0;
	int16_t f = 0;
	int16_t g = 0;
	int16_t h = 0;
	int16_t i = 0;
	
	float j = 0.0;
	float k = 0.0;
	float l = 0.0;
	float m = 0.0;
	float n = 0.0;
	float o = 0.0;
	float p = 0.0;
	float q = 0.0;
	float r = 0.0;
	

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
	a = compress_speed (0.0, SPEED_CM_S); 				// 0								=> 0 			-> OK
	b = compress_speed (10.0, SPEED_KM_H); 				// hors range +			=> 32767 	-> OK
	c = compress_speed (-10.0, SPEED_KM_H); 			// hors range -			=> -32767 -> OK
	d = compress_speed (17.7, SPEED_CM_S); 				// in range +		 		=> 4175 	-> OK
	e = compress_speed (97.22, SPEED_CM_S); 			// in range + 			=> 22936 	-> OK
	f = compress_speed (5.0, SPEED_KM_H); 				// in range +				=> 32766 	-> OK
	g = compress_speed (-17.7, SPEED_CM_S); 			// in range -				=> -4175 	-> OK
	h = compress_speed (-97.22, SPEED_CM_S); 			// in range -				=> -22937	-> OK
	i = compress_speed (-5.0, SPEED_KM_H); 				// in range -				=> -32767	-> OK
	
	a = a+b+c+d+e+f+g+h+i; // sinon ce boulet me met des warnings
	
	
	j = uncompress_speed (0, SPEED_CM_S);
	k = uncompress_speed (32767, SPEED_KM_H);
	l = uncompress_speed (-32767, SPEED_KM_H);
	m = uncompress_speed (4175, SPEED_CM_S);
	n = uncompress_speed (22936, SPEED_CM_S);
	o = uncompress_speed (32766, SPEED_KM_H);
	p = uncompress_speed (-4175, SPEED_CM_S);
	q = uncompress_speed (-22936, SPEED_CM_S);
	r = uncompress_speed (-32766, SPEED_KM_H);
	 
	j = j+k+l+m+n+o+p+q+r; // sinon ce boulet me met des warnings
	
	
// void on_car_direction_changed (uint8_t direction) {
//	car_direction_set(direction);
//	hall_sensor_init(HALL_IDENTIFIER_L, direction);
//	hall_sensor_init(HALL_IDENTIFIER_R, direction);
//	}

	car_direction_set(CAR_BW_DIRECTION);
	hall_sensor_init(HALL_IDENTIFIER_L, CAR_FW_DIRECTION);
	hall_sensor_init(HALL_IDENTIFIER_R, CAR_BW_DIRECTION);
	
	position_sensor_init();
	speed_sensor_init();
	systick_init();
	
	while(1) {
		
		car_direction_set(CAR_BW_DIRECTION);
		jeanmichelposition = position_sensor_get(POSITION_CM, 0);
		//pData_STM->travelled_distance = jeanmichelposition;
		
		jeanraymondposition = position_sensor_get(POSITION_CM, 1);
		
		jeanmichelvitesse = speed_sensor_get(SPEED_CM_S, 0);
		//pData_STM->car_speed = jeanmichelvitesse;
		
		jeanraymondvitesse = speed_sensor_get(SPEED_CM_S, 1);
	}

  return 0;
}
