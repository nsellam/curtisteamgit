#include <stdint.h>

#include "mirroring.h"

int main(void) {
   Mirroring_init();
   Mirroring_start();
   while(1){};
   return 0;
}
