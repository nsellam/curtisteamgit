/**
 * @file print.c
 * @author Curtis team
 * @brief application layer for the Raspberry Pi
 * to print any shared variables
 */




/************************
 *      LIBRARIES       *
 ************************/
#include <stdio.h>

/************************
 *      INCLUDES        *
 ************************/
#include <print.h>
#include <waitPeriod.h>
#include <data_interface.h>
#include <hdmapi.h>

/************************
 *      DEFINES         *
 ************************/



/**
 * @def PERIOD_PRINT_NS
 * @brief the period of thread print in nano seconds
 */
#define PERIOD_PRINT_NS 1000000000     // 1s

/************************
 *      VARIABLES       *
 ************************/


/********************************/
/*       FUNCTIONS              */
/********************************/

/**
 * @brief prints the content of data_PI structure
*/
void print_struct_PI(data_PI_t *D) {
  printf("\n\n\n\n\n\n\n\n\n");
  pthread_mutex_lock(&m_data_PI);
  printf("Sent:     \n");
  printf("	Motor_prop               : %i\n", D->motor_prop);
  printf("	Motor_dir                : %i\n", D->motor_dir);
  printf("	Enable_motors_contol     : %i\n", D->enable_motors_control);
  printf("	Errors_SPI               : %i\n", D->errors_SPI);
  printf("\n");
  pthread_mutex_unlock(&m_data_PI);
}

/**
 * @brief prints the content of data_STM structure
*/
void print_struct_STM(data_STM_t *D) {
  printf("Received: \n");
  printf("	Ultrasonic_Front_Right   : %i\n", D->ultrasonic_sensors[0]);//get_ultrasonic_data(US_FR));
  printf("	Ultrasonic_Front         : %i\n", get_ultrasonic_data(US_FM));
  printf("	Ultrasonic_Front_Left    : %i\n", get_ultrasonic_data(US_FL));
  printf("	Ultrasonic_Front_Right   : %i\n", get_ultrasonic_data(US_BR));
  printf("	Ultrasonic_Front         : %i\n", get_ultrasonic_data(US_BM));
  printf("	Ultrasonic_Front_Left    : %i\n", get_ultrasonic_data(US_BL));
  printf("	wheel_position_sensor_R  : %i\n", get_wheel_position(WP_R));
  printf("	wheel_position_sensor_L  : %i\n", get_wheel_position(WP_L));
  printf("	travelled_distance_R     : %f\n",    D->travelled_distance_R );  //// getter to code
  printf("	travelled_distance_L     : %f\n",    D->travelled_distance_L);  ////
  printf("	wheel_speed_R            : %f\n",    D->wheel_speed_R);  //// getter to code
  printf("	wheel_speed_L            : %f\n",    D->wheel_speed_L);  ////
  printf("	motor_current_R          : %i\n", get_motor_current(MC_R));
  printf("	motor_current_L          : %i\n", get_motor_current(MC_L));
  printf("	steering_stop_sensor_L   : %i\n", get_steering_stop_data(SS_L));
  printf("	steering_stop_sensor_R   : %i\n", get_steering_stop_data(SS_R));
  printf("	Battery_level            : %i\n", D->battery_level);              ////
  printf("	Errors_SPI               : %i\n", D->errors_SPI);
  printf("\n\n\n");
  printf("-------------------------------------------------------------");
  printf("\n");

  printf ("DATA_SIZE_MAX : %i\n", DATA_SIZE_MAX);
  printf ("ERROR_SPI_SEND : %i\n", send_error);
  printf ("canary_error_count : %i\n", canary_error_count);
  printf ("crc_error_count : %i\n", crc_error_count);
  printf ("mirroring_cycles_count : %i\n", mirroring_cycles_count);
  printf("-------------------------------------------------------------\n");
  printf("-------------------------------------------------------------");
  printf("\n\n\n");
}


/********************************/
/*       TH_PRINT               */
/********************************/



void* print(void* arg) {

  // set reference for 1st period
  clock_gettime(CLOCK_REALTIME, &T1_Print); 
  
  // periodic task
  while (1) {

    // ensure the period is respected
    waitPeriod (PERIOD_PRINT_NS, &T1_Print, &T2_Print);

    // update reference time for next call (T1_Print)   -   THIS LINE ADDS IMPERFECTION TO THE LOOP
    clock_gettime(CLOCK_REALTIME, &T1_Print);  

    // print
    print_struct_PI((data_PI_t*)pdata_PI);
    print_struct_STM((data_STM_t*)pdata_STM);
  }
}

