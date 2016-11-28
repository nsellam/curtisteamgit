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
/**
 * @def max(a,b)
 * @brief macro for maximum computing
 */
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


/**
 * @var m_data_PI
 * @brief mutex for data_PI structure
 */
pthread_mutex_t m_data_PI;

/**
 * @var m_data_STM
 * @brief mutex for data_STM structure
 */
pthread_mutex_t m_data_STM;

/**
 * @ send_error
 * @brief to store the errors when SPI sending 
 */
int send_error = 0x00;

/**
 * @ canary_error_count
 * @brief to count the canary errors 
 */
int canary_error_count = 0x00;

/**
 * @ crc_error_count
 * @brief to count the crc errors 
 */
int crc_error_count = 0x00;

int k = 0;
/************************
 *      FUNCTIONS       *
 ************************/





void * mirroringPI (void * arg) {


  uint8_t buffer_send_receive[DATA_SIZE_MAX];


  // initializations
  assert (SPI_init() >=0);
  init_data();
  pdata_PI->motor_dir = 0xBB;
  pdata_PI->led = 0xAA;
  pdata_PI->errors_SPI = 0x99;

  // set reference for 1st period
  clock_gettime(CLOCK_REALTIME, &T1); 
  
  // periodic task
  while (1) {

    // ensure the period is respected
    waitPeriod (PERIOD_MIRRORING_NS, &T1, &T2);

    // update reference time for next call (pT1)   -   THIS LINE ADDS IMPERFECTION TO THE LOOP
    clock_gettime(CLOCK_REALTIME, &T1);   ;


// thread core
    

    // create data to send (data_PI + padding)
    int i;
    for (i=0;i<sizeof(data_PI_t);i++) {
      pthread_mutex_lock(&m_data_PI);
      buffer_send_receive[i] = ((uint8_t*)pdata_PI)[i];
      pthread_mutex_unlock(&m_data_PI);
    }
  
    for (i=sizeof(data_PI_t);i<DATA_SIZE_MAX;i++) {
      buffer_send_receive[i] = PADDING;
    }


    // send - receive data from SPI
    send_error = SPI_send(buffer_send_receive, DATA_SIZE_MAX);


    // canary error -> increment canary error count
    if (send_error == SPI_CANARY_ERROR) canary_error_count++;

    // CRC error -> increment CRC error count
    if (send_error == SPI_CRC_ERROR) crc_error_count++;

    // CRC error -> increment CRC error count


    // update buffer STM if no send_error
    if ((send_error != SPI_CANARY_ERROR) && (send_error != SPI_CRC_ERROR)) {
      int j;
      for (j = 0;j < DATA_SIZE_MAX;j++) {
        pthread_mutex_lock(&m_data_STM);
        ((uint8_t*)pdata_STM)[j] = buffer_send_receive[j];
        pthread_mutex_unlock(&m_data_STM);
      }
    }

k++;


  }
}

