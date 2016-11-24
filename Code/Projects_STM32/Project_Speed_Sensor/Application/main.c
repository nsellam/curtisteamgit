#include <stdint.h>
#include "stm32f10x.h"
#include "systick.h"
#include "hall_sensor.h"


int main(void) {
	systick_init ();
	hall_sensor_init();
	
	while(1) {}

  return 0;
}
