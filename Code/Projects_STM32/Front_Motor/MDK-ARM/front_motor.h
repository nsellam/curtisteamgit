#ifndef FRONT_MOTOR_H
#define FRONT_MOTOR_H

#include <stm32f10x.h>

typedef enum {
  LEFT = 1,
  NONE = 0,
  RIGHT = -1
}Direction_TypeDef;


void front_motor_turn(Direction_TypeDef direction);
void front_motor_Callback(Direction_TypeDef direction) ;

void Turn_left(void);
void Turn_right(void);

 void front_motor_QuickInit(void);





#endif 
