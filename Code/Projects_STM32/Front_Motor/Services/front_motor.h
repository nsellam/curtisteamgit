#ifndef _FRONT_MOTOR_H
#define _FRONT_MOTOR_H

#include <stm32f10x.h>

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

/**
* @typedef Direction_TypeDef
* @brief Set the digital value for the direction LEFT=1, RIGHT=-1, and center=0.
*/
typedef enum {
  LEFT = 1,
  NONE = 0,
  RIGHT = -1
}Direction_TypeDef;

/**
 * @fn front_motor_turn
 * @brief Check the front motor's position before set an order to front motor to turn right or left
* @param Direction of front motor : LEFT(1), RIGHT(-1) or NONE(0)
*/
void front_motor_turn(Direction_TypeDef direction);

/**
 * @fn turn_left
 * @brief Give an order to front motor to turn left
* @param none
*/
void turn_left(void);

/**
 * @fn turn_right
 * @brief Give an order to front motor to turn right
* @param none
*/
void turn_right(void);

/**
 * @fn stop_front_motor
 * @brief stop the front motor
* @param none
*/
void stop_front_motor(void);

/**
 * @fn front_motor_QuickInit
 * @brief Initialisation of Exti use for front motor
* @param none
*/
void front_motor_QuickInit(void);

/**
 * @fn front_motor_Callback
 * @brief Callback service for front motor: Once the Exti rised for one direction(left or right), 
 * @brief set the speed equals to zero and get the current position(direction)
* @param none
*/
void front_motor_Callback(Direction_TypeDef direction);

#endif //_FRONT_MOTOR_H
