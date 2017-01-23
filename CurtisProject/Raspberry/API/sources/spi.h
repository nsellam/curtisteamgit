/**
 * @file spi.h
 * @author Curtis Team
 * @brief header of spi.c
 */


#ifndef SPI_H
#define SPI_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>


/********************************/
/*       DEFINES                */
/********************************/


/**
 * @def SPI_SEND_ERROR
 * @brief error code when the send function from wiringPI library faces a problem
 */ 
#define SPI_SEND_ERROR -1

/**
 * @def SPI_CANARY_ERROR
 * @brief error code when the canary is not ok
 */ 
#define SPI_CANARY_ERROR -2

/**
 * @def SPI_CRC_ERROR
 * @brief error code when the CRC is not ok
 */ 
#define SPI_CRC_ERROR -3


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