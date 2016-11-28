/**
 * @file demo.c
 * @author Curtis Team
 * @brief Demo for the SPI communication on Raspberry Pi
 * Synchronizes actuators and sensors
 */

#include <stdio.h>
#include <mirroring.h>
#include <spi.h>
#include <data.h>

int main(void) {
  SPI_init();
  init_data();

  int L = sizeof(data_PI_t);

  data_PI_t DATA = *pdata_PI;

while(1) {
    (*pdata_PI) = DATA;

    // data_PI is overwritten
    printf("%i ",SPI_send((uint8_t*)pdata_PI, L-1));

    // print
    printf("\nl : %i - sent : ", L);
}

  return 0;
}