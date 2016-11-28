/**
 * @file motor.c
 * @author Curtis team
 * @brief Service library that allows to manipulate motors
 */


/**
* @def _MOTOR_H_
* @brief to memorize if "motor.h" file has already been included
*/
#ifndef _MOTOR_H_
#define _MOTOR_H_

/********************************/
/*       LIBRARIES              */
/********************************/
#include <timer.h>
#include <gpio.h>
#include <pwm.h>


/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn motors_init
* @brief Initializes motors drivers 
* @param void
* @return void
*/
void motors_init(void);

/**
* @fn motor_set_speed
* @brief Sets motors speed 
* @param speed Speed sent to the motors between -1 and +1
* @return void
*/
void motor_set_speed(float speed);

/**
* @fn motors_start
* @brief Allows car departure with previously selected speed 
* @param void
* @return void
*/
void motors_start(void);

/**
* @fn motors_stop
* @brief Stops the car 
* @param void
* @return void
*/
void motors_stop(void);


#endif // _MOTOR_H_
