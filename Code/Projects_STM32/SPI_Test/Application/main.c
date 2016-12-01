#include <stdint.h>

#include "mirroring.h"

int main(void) {
   Mirroring_Init();
   pData_STM->ultrasonic_sensors[0] = 10;
   pData_STM->travelled_distance = 3.14;
   pData_STM->errors_SPI = 3;
   Mirroring_Start();
   while(1){};
   return 0;
}
