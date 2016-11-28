#include <stdint.h>

#include <motor.h>
#include <data.h>

#include "systick.h"
#include "hall_sensor.h"
#include "position_sensor.h"
#include "speed_sensor.h"
#include "compress.h"

#include "mirroring.h"

int main(void) {
   int i;

   volatile float motor_speed;

   motors_init();
   motors_start();

   systick_init();
   hall_sensor_init();
   position_sensor_init();
   speed_sensor_init();

   Mirroring_Init();
   Mirroring_Start();
   
   while(1) {
      motor_speed = (float)pdata_PI->motor_prop/255.0/**2.0 - 1.0*/;
      motor_set_speed(motor_speed);

      position_sensor_compute();
      pdata_STM->travelled_distance = position_sensor_get(POSITION_CM);

      speed_sensor_compute();
      pdata_STM->car_speed = speed_sensor_get(SPEED_CM_S);

      for(i = 0; i < 1e5; i++);
   }

   return 0;
}
