#ifndef __SWITCH_H__
#define __SWITCH_H__

#include <stdint.h>

void Switch_Config(void);           // external pull-up switch

uint8_t Switch_IsPressed(void);     // returns the state of the switch (1 = pressed, 0 = released)

#endif // __SWITCH_H__
