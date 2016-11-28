
#include <motor.h>


int main (void) {
	volatile float vitesse = 0.5;
   motors_init();

   
   motors_start();
   
   
   //	while (1) {
      motor_set_speed(vitesse);
      //for(i = 0; i < 1e5; i++);
   //}
   motors_stop();
   motors_start();
   while(1);
	return 0;
}
