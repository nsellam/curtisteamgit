
#include "motor.h"
#include "pwm.h"

int main (void) {
   volatile int aux = 0;
   volatile float speed = 1;
   
   motors_init();
   motor_set_speed(speed);
   motors_start();

  while (1) {
     for(aux=0; aux<1e4; aux++){}
      motor_set_speed(speed);
  }  
   
	return 0;
}
