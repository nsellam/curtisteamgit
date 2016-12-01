#include <stdint.h>

#include "mirroring.h"

int main(void) {
   mirroring_init();
   pdata_STM->ultrasonic_sensors[0] = 10;
   pdata_STM->travelled_distance = 3.14;
   pdata_STM->errors_SPI = 3;
   mirroring_start();
   while(1){};
   return 0;
}
