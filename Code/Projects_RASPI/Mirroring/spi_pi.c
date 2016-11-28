


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
#include <CRC.h>



/********************************/
/*       ALIAS                  */
/********************************/

#define SPI_SPEED 2e6

#define SPI_CHANNEL 0

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
    int error;
    int i, j;

    // temporary buffer for SPI (it will contain the structure, the CRC and the CANARI)
    uint8_t tmp[length+1];
    for (i = 0; i < length; i++) {
        tmp[i] = pdata[i];
    }

    // CRC

    //uint8_t CRC = compute_CRC(pdata, length);
    //tmp[length] = CRC;

    // SPI send/receive
    error = wiringPiSPIDataRW (SPI_CHANNEL, (uint8_t*)&tmp, length);

    // update the data structure given as a parameter with the received value
    for (j = 0; j < length; j++) {
        ((uint8_t*)(pdata))[j] = tmp[j];
    }


    return error;
}



