//__________________________________________________________
// BINOME : 
// ETAT : 
//__________________________________________________________

// registres de périphériques du stm32
#include "stm32f10x.h"

#include <system_stm32f10x.h>
#include <motor.h>


int main (void) {
	volatile float vitesse = 1;

   motors_init();

   motor_set_speed(vitesse);

   motors_start();
   

	while (1) {}
   
	
	
	return 0;
}
