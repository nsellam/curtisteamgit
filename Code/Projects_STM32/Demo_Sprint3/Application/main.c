#include <stdint.h>

#include <data.h>

#include "motor.h"
#include "systick.h"
#include "hall_sensor.h"
#include "position_sensor.h"
#include "speed_sensor.h"
#include "compress.h"
#include "car.h"
#include "adc.h"

#include "mirroring.h"



int main(void) {
   int i;

   volatile float motor_speed = 0.0;

	 init_data();
   motors_init();
   motors_start();

  
   position_sensor_init();
	 speed_sensor_init();
	 systick_init();
	
		// marche avant 
		car_direction_set(CAR_FW_DIRECTION);
		hall_sensor_start(HALL_IDENTIFIER_L, car_direction_get());
	  hall_sensor_start(HALL_IDENTIFIER_R, car_direction_get());

   Mirroring_Init();
   Mirroring_Start();
   pdata_PI->motor_prop = 127;

   while(1) {
		  // Update motor speed
      motor_speed = ((float)pdata_PI->motor_prop - 127.0)/128.0;
      motor_set_speed(motor_speed);
		 
		  // Update travelled distance & car speed fields
		  //pdata_STM->travelled_distance = position_sensor_get(POSITION_CM, 0);
		  pdata_STM->car_speed = speed_sensor_get(SPEED_CM_S, 0);

		  // Update current
		 	pdata_STM->motor_current_R = Get_ADC_Mot_D();
	    pdata_STM->motor_current_L = Get_ADC_Mot_G();
      for(i = 0; i < 1e5; i++);
   }

   return 0;
}
