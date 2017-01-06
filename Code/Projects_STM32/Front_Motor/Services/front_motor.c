#include "front_motor.h"
#include "motor.h"
#include "exti.h"

/**
* @def HARD_STOP_GPIO_LEFT
* @brief GPIO of the front motor's left direction sensor
*/
#define HARD_STOP_GPIO_LEFT GPIOC

/**
* @def HARD_STOP_GPIO_RIGHT
* @brief GPIO of the front motor's right direction sensor
*/
#define HARD_STOP_GPIO_RIGHT GPIOC

/**
* @def HARD_STOP_PIN_LEFT
* @brief GPIO pin of the front motor's left direction sensor
*/
#define HARD_STOP_PIN_LEFT 10

/**
* @def HARD_STOP_PIN_RIGHT
* @brief GPIO pin of the front motor's right direction sensor
*/
#define HARD_STOP_PIN_RIGHT 11

/**
* @def FRONT_LINE_LEFT
* @brief EXTI_line of the front motor's left direction sensor
*/
#define FRONT_LINE_LEFT EXTI_Line10

/**
* @def FRONT_LINE_RIGHT
* @brief EXTI_line of the front motor's right direction sensor
*/
#define FRONT_LINE_RIGHT EXTI_Line11

/**
* @def HARD_STOP_TRIGGATION
* @brief EXTI_line rising signal
*/
#define HARD_STOP_TRIGGATION EXTI_Trigger_Rising

/**
* @def HARD_STOP_PRIORITY
* @brief Set the priority for the Exti of front_motor
*/
#define HARD_STOP_PRIORITY 5

Direction_TypeDef front_motor_speed;
Direction_TypeDef front_motor_position;

/**
 * @fn front_motor_Callback
 * @brief Callback service for front motor: Once the Exti rised for one direction(left or right), 
 * @brief set the speed equals to zero and get the current position(direction)
* @param none
*/
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

/**
 * @fn turn_left
 * @brief Give an order to front motor to turn left
* @param none
*/
void turn_left(void){
	front_motor_set_speed((float) LEFT);
    front_motor_start();
  
}

/**
 * @fn turn_right
 * @brief Give an order to front motor to turn right
* @param none
*/
void turn_right(void){
	front_motor_set_speed((float) RIGHT);
    front_motor_start();
}

/**
 * @fn stop_front_motor
 * @brief stop the front motor
* @param none
*/
void stop_front_motor(void){
    front_motor_set_speed((float) NONE);
    front_motor_start();
}

/**
 * @fn front_motor_turn
 * @brief Check the front motor's position before set an order to front motor to turn right or left
* @param Direction of front motor : LEFT(1), RIGHT(-1) or NONE(0)
*/
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
            //front_motor_stop();   
		}
		else {};
	}

	else {
		front_motor_stop();
	}
}

/**
 * @fn front_motor_QuickInit
 * @brief Initialisation of Exti use for front motor
* @param none
*/
 void front_motor_QuickInit(void) {
		EXTI_QuickInit(HARD_STOP_GPIO_LEFT, HARD_STOP_PIN_LEFT, HARD_STOP_TRIGGATION, HARD_STOP_PRIORITY);
		EXTI_QuickInit(HARD_STOP_GPIO_RIGHT, HARD_STOP_PIN_RIGHT, HARD_STOP_TRIGGATION, HARD_STOP_PRIORITY);
        front_motor_init();
 } 
