#include <stdint.h>
#include <stm32f10x.h>
#include <battery.h>

/**
* @var Battery_Level
* @brief Battery_level in percentage
*/
uint8_t Battery_Level;


int main(void) {
	//Get the battery level in percentage
    Battery_Level = Battery_GetLevel();
    
    while(1){}
    return 0;
}
