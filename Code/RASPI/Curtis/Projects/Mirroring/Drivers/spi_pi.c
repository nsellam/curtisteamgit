


/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>
#include <wiringPiSPI.h>
#include <spidev.h>         //   /usr/include/linux/spi

/********************************/
/*      INCLUDES                */
/********************************/

#include "spi.h"

#include "stdio.h"
#include "CRC.h"



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
    int i;
    uint8_t tmp[length+1];
    for (i = 0; i < length; i++) {
        tmp[i] = pdata[i];
    }

    uint8_t CRC = compute_CRC(pdata, length);
    tmp[length] = CRC;

    error = wiringPiSPIDataRW (SPI_CHANNEL, (uint8_t*)&tmp, length + 1);
    return error;
}



int SPI_receive(uint8_t * pdata, int length) {
    int size;

    size = wiringPiSPIDataRW (SPI_CHANNEL, pdata, length+1);
    if (check_CRC(pdata, length, pdata[length]) != 0) {
        size = -1;
    }
    return size;
}

/*

int main() {

SPI_init();
int DATA = 0xAABBCC11;
uint8_t * pDATA = (uint8_t*)&DATA;
int L = sizeof(int);

while(1) {
    printf("%i ",SPI_send(pDATA, L));
    //usleep(10);
}


return 0;
}*/