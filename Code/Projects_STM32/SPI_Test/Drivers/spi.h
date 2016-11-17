
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
* @brief initializes SPI device 
* @param length: the data to send -> int
* @return : 0 if successful / -1 if error -> int
*/

int SPI_init(uint8_t * buffer_Rx, uint8_t * buffer_Tx, size_t bufferSize_Rx, size_t bufferSize_Tx);

/**
* @fn SPI_start
* @brief start the SPI communication
* @return : 0 if successful / -1 if error -> int
*/

int SPI_start(void);

/**
* @fn SPI_stop
* @brief stop the SPI communication
* @return : 0 if successful / -1 if error -> int
*/

int SPI_stop(void);

#endif // _SPI_H_
