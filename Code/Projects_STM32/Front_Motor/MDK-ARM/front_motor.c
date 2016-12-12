#include "front_motor.h"
#include "motor.h"
#include "exti.h"


#define HARD_STOP_GPIO_LEFT GPIOC
#define HARD_STOP_GPIO_RIGHT GPIOC

#define HARD_STOP_PIN_LEFT 10
#define HARD_STOP_PIN_RIGHT 11

#define HARD_STOP_TRIGGATION EXTI_Trigger_Rising

#define HARD_STOP_PRIORITY 5


Direction_TypeDef front_motor_position;
Direction_TypeDef front_motor_speed;


void front_motor_Callback(Direction_TypeDef direction) {
	if (direction ==  LEFT) { 
		front_motor_speed = NONE;
		front_motor_position = LEFT;
	}
	else if (direction ==  RIGHT) {		
		front_motor_speed = NONE;
		front_motor_position = RIGHT;
	}
	
}

//uint8_t Check_front_motor_state(void){
//	uint8_t state = 0.0; //
//	return state;
//}


void turn_left(void){
	front_motor_init();
	front_motor_set_speed((float) LEFT);
}

void turn_right(void){
	front_motor_init();
	front_motor_set_speed((float) RIGHT);
}

void front_motor_turn(Direction_TypeDef direction) {
	if (direction == LEFT) {
		if (front_motor_position != LEFT) {
			turn_left();
			front_motor_speed = LEFT; 
			front_motor_position = NONE;
		}
		else {};

	}

	else if (direction == RIGHT) {
			if (front_motor_position != RIGHT) {
			turn_right();
			front_motor_speed = RIGHT; 
			front_motor_position = NONE;
		}
		else {};
	}

	else {
		front_motor_stop();
	}
}

 void front_motor_QuickInit(void) {
		EXTI_QuickInit(HARD_STOP_GPIO_LEFT, HARD_STOP_PIN_LEFT, HARD_STOP_TRIGGATION, HARD_STOP_PRIORITY);
		EXTI_QuickInit(HARD_STOP_GPIO_RIGHT, HARD_STOP_PIN_RIGHT, HARD_STOP_TRIGGATION, HARD_STOP_PRIORITY);
    front_motor_init();
 } 
 


