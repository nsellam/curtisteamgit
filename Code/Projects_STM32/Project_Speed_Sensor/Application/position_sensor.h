#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include <stdint.h>
#include "car.h"

/**
 * @fn hall_sensor_get_lap
 * @brief 
*/
void position_sensor_init (void);

/**
 * @fn hall_sensor_get_lap
 * @brief 
 * @param 
 * @return 
 * @retval 
*/
float position_sensor_get (void);

/**
 * @fn hall_sensor_get_lap
 * @brief 
*/
void position_sensor_compute (void);

#endif //POSITION_SENSOR_H
