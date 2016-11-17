
#ifndef _SPI_H_
#define _SPI_H_

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stdint.h>
#include <stddef.h>

/********************************/
/*       ALIAS                  */
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
* @brief Initializes the SPI device with circular DMA on the given buffers.
* @param buffer_Rx: pointer to the buffer where the received data is stored
* @param buffer_Tx: pointer to the buffer where the data to send is stored
* @param bufferSize_Rx: size of buffer_Rx in bytes
* @param bufferSize_Tx: size of buffer_Tx in bytes
* @return None
*/

void SPI_init(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t bufferSize_Rx, size_t bufferSize_Tx);

/**
* @fn SPI_start
* @brief Starts the SPI communication.
* @return None
*/

void SPI_start(void);

/**
* @fn SPI_stop
* @brief Stops the SPI communication.
* @return None
*/

void SPI_stop(void);

#endif // _SPI_H_
