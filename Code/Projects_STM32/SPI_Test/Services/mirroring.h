#ifndef _MIRRORING_H_
#define _MIRRORING_H_

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
 * @brief Data of the sensors, written by the STM32.
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
 * @brief Data of the actuators, written by the Raspberry Pi.
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
* @fn Mirroring_init
* @brief Initialize the mirroring for both sensors (sent) and actuators (received).
* @return None
*/

void Mirroring_init(void);

/**
* @fn Mirroring_start
* @brief Starts the mirroring.
* @return None
*/

void Mirroring_start(void);

/**
* @fn Mirroring_stop
* @brief Stops the mirroring.
* @return None
*/

void Mirroring_stop(void);

#endif // _MIRRORING_H_
