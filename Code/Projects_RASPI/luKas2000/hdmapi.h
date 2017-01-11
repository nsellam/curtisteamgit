#ifdef __cplusplus
extern "C" {
#endif //_C++

#ifndef HDMAPI_H
#define HDMAPI_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>


  /**
   * @fn get_ultrasonic_data
   * @brief returns the distance given by an ultrasonic sensor after reading in 'data' (car state) structure
   * @param id : the id of the ultrasonic sensor -> int
   * @return : the distance in cm -> int, -1 if error
   */

  int get_ultrasonic_data(int id);


  /**
   * @fn get_wheel_position_sensor
   * @brief returns wheel position information
   * @param id : the id of the wheel position sensor -> int
   * @return : the position : TODO !!!, -1 if error
   */

  //  int get_wheel_position_data(int id);


  /**
   * @fn get_steering_stop_sensor
   * @brief returns wheel position information
   * @param id : the id of the steering stop sensor -> int
   * @return : 0 -> steering not at its limit / 1 steering at its limit, -1 if error
   */

  //  int get_steering_stop_data(int id);


  /**
   * @fn get_travelled_distance
   * @brief returns the travelled distance (cm)
   * @return : the travelled distance in cm
   */

  float get_travelled_distance();


  /**
   * @fn get_car_speed
   * @brief returns the car speed (cm/s)
   * @return : the car speed in cm/s
   */

  float get_car_speed();


  /**
   * @fn get_steering_stop_sensor
   * @brief returns wheel position information
   * @param id : the id of the steering stop sensor -> int
   * @return : 0 -> steering not at its limit / 1 steering at its limit, -1 if error
   */

  void set_motor_speed_data(uint8_t speed);

  uint8_t get_motor_speed_data();

  uint8_t get_battery_state();

#ifdef __cplusplus
}
#endif //_C++

#endif
