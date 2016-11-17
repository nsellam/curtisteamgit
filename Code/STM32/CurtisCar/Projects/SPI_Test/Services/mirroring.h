#ifndef MIRRORING_H
#define MIRRORING_H

/**
 * @file mirroring.h
 * @author Curtis Team
 * @brief common header to mirroring_pi and mirroring_st
 * This header contains structures of sensors and actuators
 */

#include <stdint.h>

/************************
 *      STRUCTURES      *
 ************************/

/**
 * @struct sensors
 * @brief data of the sensors, written by the STM32
 * size: 10 bytes
 */
typedef struct sensors {
  uint8_t ultrasonic_sensors[6];

  uint8_t wheel_position_sensor_R;
  uint8_t wheel_position_sensor_L;
  
  uint8_t steering_stop_sensor_R;
  uint8_t steering_stop_sensor_L;
} sensors_t;

extern volatile sensors_t *psensors;




/**
 * @struct actuators
 * @brief data of the actuators, written by the Raspberry Pi
 * size: 10 bytes
 */

typedef struct actuators {
  uint8_t steering_stop_sensor_R;
  uint8_t steering_stop_sensor_L;
  uint8_t motor_dir;
  uint8_t led;
} actuators_t;

extern volatile actuators_t *pactuators; 


/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn sync_sensors
 * @brief synchronizes the value of the sensors
 * @return 0 if successful / -1 if error
 */
int sync_actuators(void);

/**
 * @fn sync_actuators
 * @brief synchronizes the value of the sensors
 * @return 0 if successful / -1 if error
 */
int sync_sensors(void);

#endif //MIRRORING_H
