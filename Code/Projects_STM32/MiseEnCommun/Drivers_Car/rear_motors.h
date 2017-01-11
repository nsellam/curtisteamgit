/**
 * @file rear_motors.h
 * @author Curtis team
 * @brief Service library for rear_motors (control)
 */

#ifndef _REAR_MOTORS_H_
#define _REAR_MOTORS_H_


#include <stm32f10x_conf.h>

extern volatile int16_t speed_cmd;


#define MOTORS_COMMAND_TIME_BETWEEN_TWO_UPDATES 1



/**
 * @brief		Computes the next iteration Motor Duty-Cycle command
*/

float ComputeMotorCommand(int16_t speed_cmd, int16_t current, int16_t speed);


/**
 * @brief		Applies a PI controller to the input
*/

float PI_Controller (int32_t in);

/**
 * @brief		the core of the control loop for Left rear motor
*/
void rear_motor_L_control(int16_t cmd);



#endif
