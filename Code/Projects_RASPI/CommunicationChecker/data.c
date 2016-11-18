/************************
 *       HEADERS        *
 ************************/
#include "data.h"

/************************
 *      VARIABLES       *
 ************************/
/**
* @struct data
* @brief describes all the data containing car state that are sent by STM
*/
data_STM_t data_STM; data_STM_t *pdata_STM = &data_STM;

/**
* @struct data
* @brief describes all the data containing car state that are sent by Pi
*/
data_Pi_t data_Pi; data_Pi_t *pdata_Pi = &data_Pi;

/**
* @struct data
* @brief describes all the data containing car state
*/
data_t data; data_t *pdata = &data; 


/************************
 *      FUNCTIONS       *
 ************************/


 
void init_data_STM(void) {
  data_STM.ultrasonic_sensors[0] = 0x00;
  data_STM.ultrasonic_sensors[1] = 0x00;
  data_STM.ultrasonic_sensors[2] = 0x00;
  data_STM.ultrasonic_sensors[3] = 0x00;
  data_STM.ultrasonic_sensors[4] = 0x00;
  data_STM.ultrasonic_sensors[5] = 0x00;
  data_STM.wheel_position_sensor_R = 0x00; 
  data_STM.wheel_position_sensor_L = 0x00;   
  data_STM.steering_stop_sensor_R = 0x00;
  data_STM.steering_stop_sensor_L = 0x00;
  data_STM.errors_SPI = 0x00;
}



void init_data_Pi(void) {
  data_Pi.motor_prop = 0x00;
  data_Pi.motor_dir = 0x00;
  data_Pi.led = 0x00;
  data_Pi.errors_SPI = 0x00;
}


void init_data(void){
  data.data_STM = data_STM;
  data.data_Pi = data_Pi;
}


