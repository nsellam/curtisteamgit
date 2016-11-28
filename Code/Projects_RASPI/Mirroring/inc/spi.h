
#ifndef SPI_H

/**
* @def SPI_H
* @brief to memorize if "fifo.h" file has already been included
*/

#define SPI_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>


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
* @return : 0 if successful / -1 if error -> int
*/

int SPI_init(void);




/**
* @fn SPI_send
* @brief sends data with SPI device  
* @param pdata : pointer to the data to send  -> ptr
* @return : size of transmitted data / -1 if error -> int
*/

int SPI_send(uint8_t * pdata, int length);





#endif