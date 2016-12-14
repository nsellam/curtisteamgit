#include <stdint.h>
#include <stm32f10x.h>
#include <battery.h>

//Vbat PB0
uint8_t Battery_Level;
int main(void) {
	
    Battery_Level = Battery_GetLevel();
    
    while(1){}
    return 0;
}
