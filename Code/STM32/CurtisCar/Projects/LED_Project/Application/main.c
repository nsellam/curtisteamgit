#include <stdint.h>

#include "stm32f10x.h"
#include "led.h"
#include "switch.h"

int main(void) {

   LED_Config();
   Switch_Config();

   while(1) LED_Write(Switch_IsPressed());

   return 0;
}
