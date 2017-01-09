/**
 * @file motor.c
 * @author Curtis team
 * @brief Service library that allows to manipulate motors
 */

#include <stdint.h>

/**
* @def _MOTOR_H_
* @brief to memorize if "motor.h" file has already been included
*/
#ifndef _MOTOR_H_
#define _MOTOR_H_

/**
* @def SPEED_DELTA
* @brief Variation of the speed value between its maximum or minimum value and the zero
*/
#define SPEED_DELTA ((float)1.0)

/**
* @def SPEED_MAX
* @brief Maximum speed value used to turn the motors forwards(+) or backwards(-) to their maximum
*/
#define SPEED_MAX (SPEED_DELTA)

/********************************/
/*       LIBRARIES              */
/********************************/


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


void front_motor_init(void);
void front_motor_set_speed(float speed);
void front_motor_start(void);
void front_motor_stop(void);

#endif // _MOTOR_H_

