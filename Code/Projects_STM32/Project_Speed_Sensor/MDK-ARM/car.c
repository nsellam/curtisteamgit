/**
 * @file car.c
 * @author Curtis Team
 * @brief Functions to describe the car 
 */
 
 
 
 /////// A METTRE DANS MOTOR.C ?????????
 
 
 #include "car.h"

uint8_t car_direction = CAR_FW_DIRECTION;

void car_direction_set (uint8_t direction) {
	car_direction = direction;
}

uint8_t car_direction_get (void) {
	return car_direction;
}
