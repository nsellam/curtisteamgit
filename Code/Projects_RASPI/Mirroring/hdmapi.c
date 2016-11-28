/**
 * @file hdmapi.c
 * @author Curtis team
 * @brief service layer for the Raspberry Pi
 * Functions fo modify the structure 
 */


/************************
 *      HEADERS         *
 ************************/
#include <hdmapi.h>
#include <data.h>

/************************
 *      INCLUDES        *
 ************************/
#include <stdio.h>


/************************
 *      VARIABLES       *
 ************************/



/************************
 *      FUNCTIONS       *
 ************************/



int get_ultrasonic_data(int id) {
  int tmp;  // to store the return value
  
  // ensure the id parameter is valid (between 0 and 5 included)
  if ((id >= 0) && (id < 6)) {
    pthread_mutex_lock(&m_data_STM);
    tmp = pdata_STM->ultrasonic_sensors[id];
    pthread_mutex_unlock(&m_data_STM);
  }
  else {
    tmp = -1;
  }
  return tmp;
}



int get_wheel_position_data(int id) {
  int tmp;  // to store the return value

  if (id == WP_R) {
    pthread_mutex_lock(&m_data_STM);
    tmp = pdata_STM->wheel_position_sensor_R;
    pthread_mutex_unlock(&m_data_STM);
  }
  else if (id == WP_L) {
    pthread_mutex_lock(&m_data_STM);
    tmp = pdata_STM->wheel_position_sensor_L;
    pthread_mutex_unlock(&m_data_STM);
  }
  else {
    tmp = -1;
  }
  
  return tmp;
}



int get_steering_stop_data(int id) {
  int tmp;  // to store the return value

  if (id == SS_R) {
    pthread_mutex_lock(&m_data_STM);
    tmp = pdata_STM->steering_stop_sensor_R;
    pthread_mutex_unlock(&m_data_STM);
  }
  else if (id == SS_L) {
    pthread_mutex_lock(&m_data_STM);
    tmp = pdata_STM->steering_stop_sensor_L;
    pthread_mutex_unlock(&m_data_STM);
  }
  else {
    tmp = -1;
  }
  
  return tmp;
}


/*
float get_travelled_distance() {
  float tmp;  // to store the return value
  pthread_mutex_lock(&m_data_STM);
  tmp = pdata_STM->travelled_distance;
  pthread_mutex_unlock(&m_data_STM);

  return tmp;
}



float get_car_speed() {
  float tmp;  // to store the return value
  pthread_mutex_lock(&m_data_STM);
  tmp = pdata_STM->car_speed;
  pthread_mutex_unlock(&m_data_STM);

  return tmp;
}

*/

void set_motor_speed_data(uint8_t speed) {
  pthread_mutex_lock(&m_data_PI);
  pdata_PI->motor_prop = speed;
  pthread_mutex_unlock(&m_data_PI);
}
