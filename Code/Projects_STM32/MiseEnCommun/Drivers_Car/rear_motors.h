/**
 * @file    rear_motors.h
 * @author  Curtis Team
 * @brief   Headers of functions to handle rear motors 
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _REAR_MOTORS_H
#define _REAR_MOTORS_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported variables ------------------------------------------------------------*/
extern volatile int16_t speed_cmd;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/**
 * @brief Time corresponding to a motors command period : meaning time between two changes the command. Expressed in ms. 
*/
#define MOTORS_COMMAND_TIME_BETWEEN_TWO_UPDATES 1

/* Exported functions ------------------------------------------------------- */


/**
 * @brief		the core of the control loop for Left rear motor
*/
void rear_motor_L_control (int16_t cmd);

/**
 * @brief		the core of the control loop for Right rear motor
*/
void rear_motor_R_control (int16_t speed_cmd);
    

#endif // _REAR_MOTORS_H
