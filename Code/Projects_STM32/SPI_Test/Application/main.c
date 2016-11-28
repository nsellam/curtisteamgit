#include <stdint.h>

#include "mirroring.h"

int main(void) {
   Mirroring_Init();
   pdata_STM->ultrasonic_sensors[0] = 0xCD;
   Mirroring_Start();
   while(1){};
   return 0;
}
