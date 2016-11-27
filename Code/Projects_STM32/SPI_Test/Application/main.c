#include <stdint.h>

#include "mirroring.h"

int main(void) {
   Mirroring_Init();
   Mirroring_Start();
   while(1){};
   return 0;
}
