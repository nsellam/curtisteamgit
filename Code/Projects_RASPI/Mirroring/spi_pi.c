/**
 * @file spi_pi.c
 * @author curtisTeam
 * @brief files where there are the functions for SPI communication
 */



/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>
#include <wiringPiSPI.h>
#include <spidev.h>         //   /usr/include/linux/spi

/********************************/
/*      INCLUDES                */
/********************************/

#include <spi.h>
#include <stdio.h>
#include <framecheck.h>



/********************************/
/*       ALIAS                  */
/********************************/

/**
 * @def SPI_SPEED
 * @brief the SPI clock frequency (Hz)
 */ 
#define SPI_SPEED 2e6

/**
 * @def SPI_CHANNEL
 * @brief the channel for spi on Pi
 */ 
#define SPI_CHANNEL 0

/**
 * @def SPI_MODE
 * @brief the spi mode
 */ 
#define SPI_MODE SPI_MODE_0


/********************************/
/*       VARIABLES              */
/********************************/

/********************************/
/*       STRUCTURES             */
/********************************/

/********************************/
/*       FUNCTIONS              */
/********************************/



int SPI_init(void) {
    int error;
    error = wiringPiSPISetupMode (SPI_CHANNEL, SPI_SPEED, SPI_MODE);
    return error;
}



int SPI_send(uint8_t * pdata, int length) {

    // declarations
    int error = 0x00;
    int i, j;

    // temporary buffer for SPI (it will contain the structure, the FRAME_CRC and the FRAME_CANARY)
    uint8_t tmp[length + FRAME_CANARY_SIZE + FRAME_CRC_SIZE];
    for (i = 0; i < length; i++) {
        tmp[i] = pdata[i];
    }
 
    // CANARI - 0xCA
    tmp[length] = Frame_compute_canary();
  
    // CRC
    tmp[length + FRAME_CANARY_SIZE] = Frame_compute_CRC((uint8_t*)&tmp, length + FRAME_CANARY_SIZE);

    // SPI send/receive
    error = wiringPiSPIDataRW (SPI_CHANNEL, (uint8_t*)&tmp, length + FRAME_CANARY_SIZE + FRAME_CRC_SIZE);

    // check CRC & canari
    if (Frame_check_canary(tmp[length]) != 0x00) {
      error = SPI_CANARY_ERROR;
      if (Frame_check_CRC((uint8_t*)&tmp, length + FRAME_CANARY_SIZE, tmp[length + FRAME_CANARY_SIZE]) != 0x00) error = SPI_CRC_ERROR;
    }
    

    // update the data structure given as a parameter with the received value if no error
    if ((error != SPI_CANARY_ERROR) && (error != SPI_CRC_ERROR)) {
      for (j = 0; j < length; j++) {
        ((uint8_t*)(pdata))[j] = tmp[j];
      }
    }

    return error;
}



