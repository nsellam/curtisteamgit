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
#include <data_interface.h>


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
  // return -1 if the id is not in range
  else {
    tmp = -1;
  }
  return tmp;
}

uint16_t get_motor_current(int ID) {
  uint16_t tmp;  // to store the return value
  pthread_mutex_lock(&m_data_STM);
  if (ID == MC_R) {
    tmp = pdata_STM->motor_current_R;
  }
  else if (ID == MC_L) {
    tmp = pdata_STM->motor_current_L;
  }
  else {
    tmp = -1;
  }
  pthread_mutex_unlock(&m_data_STM);
  
  return tmp;
}

int get_wheel_position(int id) {
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
  // the id does not exist
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
  // idea does not exist
  else {
    tmp = -1;
  }
  
  return tmp;
}


 
float get_travelled_distance_R() {
  float tmp;  // to store the return value
  pthread_mutex_lock(&m_data_STM);
  tmp = pdata_STM->travelled_distance_R;
  pthread_mutex_unlock(&m_data_STM);

  return tmp;
}

float get_travelled_distance_L() {
  float tmp;  // to store the return value
  pthread_mutex_lock(&m_data_STM);
  tmp = pdata_STM->travelled_distance_L;
  pthread_mutex_unlock(&m_data_STM);

  return tmp;
}



float get_wheel_speed_R() {
  float tmp;  // to store the return value
  pthread_mutex_lock(&m_data_STM);
  tmp = pdata_STM->wheel_speed_R;
  pthread_mutex_unlock(&m_data_STM);

  return tmp;
}


float get_wheel_speed_L() {
  float tmp;  // to store the return value
  pthread_mutex_lock(&m_data_STM);
  tmp = pdata_STM->wheel_speed_L;
  pthread_mutex_unlock(&m_data_STM);

  return tmp;
}
float get_battery_level () {
  float tmp; 
  pthread_mutex_lock(&m_data_STM);
  tmp = pdata_STM->battery_level;
  pthread_mutex_unlock(&m_data_STM);

  return tmp;
}



int set_motor_speed(int16_t speed) {
  int tmp;
  if (speed >= -100 && speed <= 100) {
    pthread_mutex_lock(&m_data_PI); 
    pdata_PI->motor_prop = speed;
    pthread_mutex_unlock(&m_data_PI);
    tmp = 0; 
  }
  else {
    tmp = -1; 
  }
  return tmp;
}

int set_enable_motors_control(uint8_t control) {
  int tmp;
  if (control == 1 || control == 0){
    pthread_mutex_lock(&m_data_PI);
    pdata_PI->enable_motors_control = control;  
    pthread_mutex_unlock(&m_data_PI);
    tmp = 0;
  }
  else {
    tmp = -1;
  }
  return tmp;
}

int set_car_direction(side_TypeDef dir) {
  int tmp;
  if (dir == RIGHT || dir == LEFT) {
    pthread_mutex_lock(&m_data_PI);
    pdata_PI->motor_dir = dir;
    pthread_mutex_unlock(&m_data_PI);
    tmp = 0;
  }
  else { 
    tmp = -1;
  }
  return tmp;
}

