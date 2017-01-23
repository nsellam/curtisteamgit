/**
 * @file hdmapi.h
 * @author Curtis Team
 * @brief header of hdmapi.c
 */


#ifndef HDMAPI_H
#define HDMAPI_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>
#include <data_interface.h>


/********************************/
/*       DEFINES                */
/********************************/




/********************************/
/*       VARIABLES              */
/********************************/

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*       FUNCTIONS              */
/********************************/


//------------------------------------//
// GETTERS - fields updated by the STM//
//------------------------------------//

/**
* @brief returns the distance given by an ultrasonic sensor after reading in 'data' (car state) structure
* @param id : the id of the ultrasonic sensor
* US_BL (back left ultrasonic)  /  US_BM (back mid ultrasonic)  /  US_BR (back right ultrasonic)
* US_FL (front left ultrasonic)  /  US_FM (front mid ultrasonic)  /  US_FR (front right ultrasonic)
* @return : the distance in cm -> int, -1 if error
*/
int get_ultrasonic_data(int id);


/**
* @brief returns wheel position information
* @param id : the id of the wheel position sensor
* WP_R (right wheel position sensor) / WP_L (left wheel postition sensor)
* @return : hall sensors information
*/
int get_wheel_position(int id);


/**
* @brief returns wheel position information
* @param id : the id of the steering stop sensor 
* SS_L (left steering stop sensor) / SS_R (right wheel steering stop sensor)
* @return : 0 -> steering not at its limit / 1 steering at its limit, -1 if error
*/
int get_steering_stop_data(int id);

/**
* @brief returns an image for the current (12 bit adc value)
* @param the ID of the motor current we want to know
* MC_R (right motor current) / MC_L (left motor current)
* @return : the current in mA (for the motor we chose)
*/
uint16_t get_motor_current(int ID);

/**
* @brief returns the travelled distance by right wheel (cm)
* @return : the travelled distance in cm
*/
float get_travelled_distance_R();

/**
* @brief returns the travelled distance by left wheel (cm)
* @return : the travelled distance in cm
*/
float get_travelled_distance_L();

/**
* @brief returns the left wheel speed (cm/s)
* @return : the left wheel speed in cm/s
*/
float get_wheel_speed_L();

/**
* @brief returns the right wheel speed (cm/s)
* @return : the right wheel speed in cm/s
*/
float get_wheel_speed_R();

/**
* @brief returns the battery level in %
* @return : the battery level in %
*/
float get_battery_level();


//-----------------------------------//
// SETTERS - fields updated by the PI//
//-----------------------------------//
/**
* @brief fills the field motor_prop in data_PI structure
* @param the expected speed (cm/s)
* @retval 0 if speed parameter in range [-100 / 100] / -1 otherwise
*/
int set_motor_speed(int16_t speed);

/**
* @brief fills the field motor_dir in data_PI structure
* @param the expected direction
* LEFT (turn left) / RIGHT (turn right) 
* @retval 0 if valid parameter / -1 otherwise
*/
int set_car_direction(side_TypeDef dir) ;

/**
* @brief fills the field enable_motors_control in data_PI structure
* @param do we enable control - 0 for disable - 1 for enable
- @retval -1 if invalid parameter / 0 if valid parameter
*/
int set_enable_motors_control(uint8_t control);

#endif