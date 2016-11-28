/**
 * @file mirroringPI.c
 * @author Curtis team
 * @brief service layer for the Raspberry Pi
 * Synchronizes data by sending values of actuators and receiving values of sensors
 */




/************************
 *      LIBRARIES       *
 ************************/
#include <stdio.h>

/************************
 *      INCLUDES        *
 ************************/
#include <mirroring.h>
#include <spi.h>
#include <data.h>
#include <waitPeriod.h>
#include <assert.h>
#include <pthread.h>

/************************
 *      DEFINES         *
 ************************/

#define max(a,b)  (((a) > (b)) ? (a) : (b))

/**
 * @def PERIOD_MIRRORING_NS
 * @brief the period of thread mirroringPI in nano seconds
 */
#define PERIOD_MIRRORING_NS 1000000     // 1ms


/**
 * @def PADDING
 * @brief padding byte
 */
#define PADDING 0x00

/************************
 *      VARIABLES       *
 ************************/


int k;
pthread_mutex_t m_data_PI;
pthread_mutex_t m_data_STM;

//const size_t padding_size = (DATA_SIZE_MAX-sizeof(data_STM_t));

/************************
 *      FUNCTIONS       *
 ************************/





void * mirroringPI (void * arg) {


  uint8_t buffer_send_receive[DATA_SIZE_MAX];

  // initializations
  assert (SPI_init() >=0);
  init_data();
  pdata_PI->motor_dir = 0xA5;
  pdata_PI->led = 0x0F;
  pdata_PI->errors_SPI = 0xBF;


  // set reference for 1st period
  clock_gettime(CLOCK_REALTIME, &T1); 
  
  // periodic task
  while (1) {

    // ensure the period is respected
    waitPeriod (PERIOD_MIRRORING_NS, &T1, &T2);

    // update reference time for next call (pT1)   -   THIS LINE ADDS IMPERFECTION TO THE LOOP
    clock_gettime(CLOCK_REALTIME, &T1);   ;


// thread core
    

    int i;
    for (i=0;i<sizeof(data_PI_t);i++) {
      pthread_mutex_lock(&m_data_PI);
      buffer_send_receive[i] = ((uint8_t*)pdata_PI)[i];
      pthread_mutex_unlock(&m_data_PI);
    }
  
    for (i=sizeof(data_PI_t);i<DATA_SIZE_MAX;i++) {
      buffer_send_receive[i] = PADDING;
    }


    SPI_send(buffer_send_receive, DATA_SIZE_MAX);


    int j;
    for (j = 0;j < DATA_SIZE_MAX;j++) {
      pthread_mutex_lock(&m_data_STM);
      ((uint8_t*)pdata_STM)[j] = buffer_send_receive[j];
      pthread_mutex_unlock(&m_data_STM);
    }


k++;


  }
}

