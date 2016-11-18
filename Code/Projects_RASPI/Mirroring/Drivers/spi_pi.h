#ifndef SPI_PI_H
#define SPI_PI_H

/**
 * @file spi_pi.h
 * @author Curtis Team
 * @brief header for the spi_pi.c
 */

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h> //for the uint8_t type
#include <stddef.h> //for the size_t type

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
 * @return file descriptor of the device, -1 if error
 */
int SPI_init(void);

/**
 * @fn SPI_send
 * @brief sends data with SPI device  
 * @param pdata: pointer to the data to send -> ptr
 * @param len: length of the packet to send
 * @return size of transmitted data
 * @retval -1 if error
 */
int SPI_send(uint8_t * pdata, size_t len);

/**
 * @fn SPI_receive
 * @brief receives data with SPI device  
 * @param pdata: pointer to the data to be received -> ptr
 * @param len: the data to be received -> int
 * @return size of transmitted data
 * @retval -1 if not received
 * @retval -2 if no data
 * @retval -3 if corrupted
 */
int SPI_receive(uint8_t * pdata, size_t len);

#endif //SPI_PI_H
