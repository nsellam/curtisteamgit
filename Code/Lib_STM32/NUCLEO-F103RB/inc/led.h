#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

void LED_Config(void);

void LED_On(void);            // turns LED on
void LED_Off(void);           // turns LED off
void LED_Toggle(void);        // toggles LED
void LED_Write(uint8_t val);  // if val > 0, ON else OFF

#endif // __LED_H__
