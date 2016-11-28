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
#include <data.h>
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

void print_struct_PI(data_PI_t *D) {
  pthread_mutex_lock(&m_data_PI);
  printf("Sent:     \n");
  printf("	Motor_prop               : %i\n", D->motor_prop);
  printf("	Motor_dir                : %i\n", D->motor_dir);
  printf("	LED                      : %i\n", D->led);
  printf("	Errors_SPI               : %i\n", D->errors_SPI);
  printf("        Canari                   : %i\n", D->canari);
  printf("        CRC                      : %i\n", D->CRC);
  printf("\n");
  pthread_mutex_unlock(&m_data_PI);
}

void print_struct_STM(data_STM_t *D) {
  printf("Received: \n");
  printf("	Ultrasonic_Front_Right   : %i\n", D->ultrasonic_sensors[0]);//get_ultrasonic_data(US_FR));
  printf("	Ultrasonic_Front         : %i\n", get_ultrasonic_data(US_FM));
  printf("	Ultrasonic_Front_Left    : %i\n", get_ultrasonic_data(US_FL));
  printf("	Ultrasonic_Front_Right   : %i\n", get_ultrasonic_data(US_BR));
  printf("	Ultrasonic_Front         : %i\n", get_ultrasonic_data(US_BM));
  printf("	Ultrasonic_Front_Left    : %i\n", get_ultrasonic_data(US_BL));
  printf("	wheel_position_sensor_R  : %i\n", get_wheel_position_data(WP_R));
  printf("	wheel_position_sensor_L  : %i\n", get_wheel_position_data(WP_L));
  //printf("	travelled_distance       : %f\n", get_travelled_distance());
  //printf("	car_speed                : %f\n", get_car_speed());
  printf("	steering_stop_sensor_R   : %i\n", get_steering_stop_data(SS_R));
  printf("	steering_stop_sensor_L   : %i\n", get_steering_stop_data(SS_L));
  printf("	Errors_SPI               : %i\n", D->errors_SPI);
  printf("        CANARI                   : %i\n", D->canari);
  printf("        CRC                      : %i\n", D->CRC);
  printf("\n\n\n");
  printf("-------------------------------------------------------------");
  printf("\n");

  printf ("DATA_SIZE_MAX : %i\n\n", DATA_SIZE_MAX);
  printf ("float         : %i\n", sizeof(float));
  printf ("data_stm      : %i\n", sizeof(data_STM_t));
  printf ("data_pi      : %i\n", sizeof(data_PI_t));
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

