#include "test_hdmapi.h"

static int us[6] = {92,92,100,25,18,12};
static float km = 0;
static float carspeed = 0;
static int battery = 92;
static int motorspeed = 0;

int get_ultrasonic_data_test(int id) {
  int tmp;  // to store the return value
  
  // ensure the id parameter is valid (between 0 and 5 included)
  if ((id >= 0) && (id < 6)) {
    //pthread_mutex_lock(&m_data_STM);
    //tmp = pdata_STM->ultrasonic_sensors[id];
    //pthread_mutex_unlock(&m_data_STM);
    if (id < 3) {
      us[id] -= 4;
    } else {
      us[id] += 4;
    }
    tmp = us[id];
  }
  // return -1 if the id is not in range
  else {
    tmp = -1;
  }
  return tmp;
}
/*
int get_wheel_position_data_test(int id) {
  int tmp;  // to store the return value

  if (id == WP_R) {
    //pthread_mutex_lock(&m_data_STM);
    //tmp = pdata_STM->wheel_position_sensor_R;
    //pthread_mutex_unlock(&m_data_STM);
  
  }
  else if (id == WP_L) {
    //pthread_mutex_lock(&m_data_STM);
    //tmp = pdata_STM->wheel_position_sensor_L;
    //pthread_mutex_unlock(&m_data_STM);
  }
  // the id does not exist
  else {
    tmp = -1;
  }
  
  return tmp;
}

int get_steering_stop_data_test(int id) {
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
*/

float get_travelled_distance_test() {
  float tmp;  // to store the return value
  //pthread_mutex_lock(&m_data_STM);
  //tmp = pdata_STM->travelled_distance;
  //pthread_mutex_unlock(&m_data_STM);
  km += 115;
  tmp = km;
  return tmp;
}

float get_car_speed_test() {
  float tmp;  // to store the return value
  //pthread_mutex_lock(&m_data_STM);
  //tmp = pdata_STM->car_speed;
  //pthread_mutex_unlock(&m_data_STM);
  if (carspeed < 105) {
    carspeed += 11.0;
  } else {
    carspeed -= 8.0;
  }
  tmp = carspeed;
  return tmp;
}

void set_motor_speed_data_test(uint8_t speed) {
  //pthread_mutex_lock(&m_data_PI);
  //pdata_PI->motor_prop = speed;
  //
  motorspeed = speed;
}

uint8_t get_motor_speed_data_test() {
  return motorspeed;
}

uint8_t get_battery_state_test() {
  battery -= 4;
  return battery;
}

