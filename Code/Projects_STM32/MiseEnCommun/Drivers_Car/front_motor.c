/**
 * @file    front_motor.c
 * @author  Curtis Team
 * @brief   Functions to handle front motor  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "front_motor.h"
#include "modules_definitions.h"
#include "motors.h"
#include "exti.h"
#include "modules_definitions.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
side_TypeDef FrontMotor_position = NONE;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Initialisation of Exti use for front motor
 * @retval  None
*/
void FrontMotor_QuickInit(void) {
    Motor_QuickInit(FRONT_MOTOR);
    EXTI_QuickInit(HARD_STOP_GPIO_LEFT, HARD_STOP_PIN_LEFT, HARD_STOP_TRIGGATION, HARD_STOP_PRIORITY);
    EXTI_QuickInit(HARD_STOP_GPIO_RIGHT, HARD_STOP_PIN_RIGHT, HARD_STOP_TRIGGATION, HARD_STOP_PRIORITY);
}

/**
 * @brief   Check the front motor's position before set an order to front motor to turn right or left
 * @param   Direction of front motor
*/
void front_motor_turn(side_TypeDef direction) {
	if (direction == LEFT) {
		if (FrontMotor_position != LEFT) {
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
/* Private functions ---------------------------------------------------------*/
