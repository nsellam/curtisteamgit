/********************************/
/*       LIBRARIES              */
/********************************/

#include <wiringPiSPI.h>
#include <spidev.h>         //   /usr/include/linux/spi

/********************************/
/*      INCLUDES                */
/********************************/

#include "spi.h"
#include "CRC.h"

/********************************/
/*       DEFINE                 */
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

/**
 * @fn SPI_init
 * @brief configures the SPI peripherals
 * @return file descriptor of the device, -1 if error
 */
int SPI_init(void) {
  return wiringPiSPISetupMode (SPI_CHANNEL, SPI_SPEED, SPI_MODE);
}

/**
 * @fn SPI_send
 * @brief sending the packet, adding canary and CRC
 * Copying the data in a new packet, then adding the canary and a CRC
 * @param pdata: pointer to the begining of the sending data
 * @param len: length of the packet to send
 * @return: size of the transmitted data, -1 if error
 */
int SPI_send(uint8_t * pdata, size_t len) {
  int size;
  int i;
  uint8_t tmp[len+2]; //tmp: buffer containing the packet to send
  for (i = 0; i < len; i++) {
    tmp[i] = pdata[i];
  }
    
  /* +-----------------------------------+
   * |ac1|ac2|ac3|ac4|ac5|ac6|err|can|CRC|
   * +-----------------------------------+

   * +-----------------------------------+
   * |            data           |can|CRC|
   * +-----------------------------------+
   */
    
  /* add canary (len) */
  uint8_t canary = CANARY; //à mettre dans spi.h
  tmp[len] = canary;
  /* add CRC (len+1) */
  uint8_t CRC = compute_CRC(pdata, len);
  tmp[len+1] = CRC;

  if ( !size = wiringPiSPIDataRW (SPI_CHANNEL, (uint8_t*)&tmp, len+ 1) ) {
    //check si erreur
  }
  return size;
}

/**
 * @fn SPI_receive
 * @brief reception of data from the STM32, and checking
 * @param pdata: pointer to the beginning of the buffer
 * @param len: length of the packet
 * @return size: size of ???, -1 if no data, -2 if corrupted
 */
int SPI_receive(uint8_t * pdata, size_t len) {
  int size;

  if ( !size = wiringPiSPIDataRW (SPI_CHANNEL, pdata, len+1) ) {
    //check si erreur;
  }
  
  if (check_canary(pdata[len-1])) {
    size = -1; //the canary is empty => no data
  } else {
    if (check_CRC(pdata, len, pdata[len])) {
      size = -2; //the CRC is corrupted => file corrupted
    }
  }
  
  return size;
}
