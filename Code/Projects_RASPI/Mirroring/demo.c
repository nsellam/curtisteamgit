/**
 * @file demo.c
 * @author Curtis Team
 * @brief Demo for the SPI communication on Raspberry Pi
 * Synchronizes actuators and sensors
 */

#include <stdio.h>

#include <mirroring.h>
#include <spi.h>
#include <data.h>

int main(void) {
  
  int LED_state;
 
  SPI_init();
  init_data_Pi();
  init_data_STM();
  
  while(1) {
    
printf("dbg1\n");
    LED_state = pdata_Pi->led;
printf("dbg2 : %c\n", LED_state);
    
    if (LED_state == '0') {
      printf("LED is off, turn on?\n");
    } else 
    if (LED_state == '1') {
      printf("LED is on, turn off?\n");
    }
    
    int param;
    while( (param = fgetc(stdin)) != '\n') {

      if (param == '0') {
	if (LED_state == '1') {
          pdata_Pi->led = '0';
          sync_data_Pi();
      	}
      } else 
      if (param == '1') {
      	if (LED_state == '0') {
      	  pdata_Pi->led = '1';
      	  sync_data_Pi();
      	}  
      } else {
     	printf("ERROR : invalid argument\n");
      }
    }
  }
  return 0;
}