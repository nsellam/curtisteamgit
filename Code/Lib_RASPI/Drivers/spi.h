#ifndef SPI_H
#define SPI_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>

/********************************/
/*       DEFINE                 */
/********************************/

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
 * @brief initializes SPI device  
 * @return : file descriptor of the device, -1 if error
 */
int SPI_init(void);

/**
 * @fn SPI_send
 * @brief sends data with SPI device  
 * @param pdata: pointer to the data to send -> ptr
 * @param len: length of the packet to send
 * @return: size of transmitted data / -1 if error -> int
 */
int SPI_send(uint8_t * pdata, size_t len);

/**
 * @fn SPI_receive
 * @brief receives data with SPI device  
 * @param pdata: pointer to the data to be received -> ptr
 * @param len: the data to be received -> int
 * @return size of transmitted data, -1 if error -> int
 */
int SPI_receive(uint8_t * pdata, size_t len);

#endif //SPI_H
