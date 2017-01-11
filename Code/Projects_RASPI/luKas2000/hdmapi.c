#include "hdmapi.h"
#include <stdio.h>

static int obstacle_front = 2000;
static int current_position = 200;
static int obstacle_rear = 0;
//vitesse max : 150 cm/s

static int us[6] = {100,100,100,20,20,20};
static float km = 0;
static float carspeed = 0;
static int battery = 100;
static int motorspeed = 0;
static int moveforward = 1;

void set_motor_speed_data(uint8_t speed) {
    if (speed > 127) {
        motorspeed = speed - 255;
    } else {
        motorspeed = speed;
    }
    printf("%d\n", motorspeed);
}

uint8_t get_motor_speed_data() {
  return motorspeed;
}

float get_car_speed() {
    if (motorspeed < 0) {
        carspeed = (-1.18)*(motorspeed);
        moveforward = 0;
    } else if (motorspeed > 0) {
        carspeed = 1.18*(motorspeed);
        moveforward = 1;
    } else {
        carspeed = 0;
    }
    return carspeed;
}

float get_travelled_distance() {
  if (moveforward) {
    current_position += carspeed/10;
  } else {
    current_position -= carspeed/10;
  }
  km += carspeed/10;
  return km;
}

int get_ultrasonic_data(int id) {
  // ensure the id parameter is valid (between 0 and 5 included)
  if ((id >= 0) && (id < 6)) {
      if(id < 3) {
        if (obstacle_front - current_position > 1000) {
          us[id] = 100;
        } else {
          us[id] = (obstacle_front - current_position)/10;
        }
      } else {
        if (current_position - obstacle_rear > 1000) {
          us[id] = 100;
        } else {
          us[id] = (current_position - obstacle_rear)/10;
        }
      }
  }
  return us[id];
}

uint8_t get_battery_state() {
  battery = 100-(km/100) ;
  return battery;
}

