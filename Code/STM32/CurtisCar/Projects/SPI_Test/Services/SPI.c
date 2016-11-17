
/********************************/
/*       LIBRARIES              */
/********************************/
#include <SPI.h>
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "MX_gpio.h"
#include "MX_dma.h"
#include "MX_spi.h"

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
* @param length : the data to send -> int
* @return : 0 if successful / -1 if error -> int
*/

int SPI_init(void){

	  /* Initialize all configured peripherals */
	  MX_GPIO_Init();
	  MX_DMA_Init();
	  MX_SPI2_Init();
	
	return 0;
}




/**
* @fn SPI_send
* @brief sends data with SPI device  
* @param pdata : pointer to the data to send  -> ptr
* @param length : the data to send  -> int
* @return : 0 if successful / -1 if error -> int
*/

int SPI_send(uint8_t * pdata, int length){
	if(HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*)pdata, length) != HAL_OK)	return -1;
	else 	return 0;
}



/**
* @fn SPI_receive
* @brief receives data with SPI device  
* @param pdata : pointer to the data to send  -> ptr
* @param length : the data to send  -> int
* @return : 0 if successful / -1 if error -> int
*/

int SPI_receive(uint8_t * pdata, int length){
	if(HAL_SPI_Receive_DMA(&hspi2, (uint8_t*)pdata, length) != HAL_OK)
		return -1; // length+1 for CRC
	else if(HAL_SPI_GetError(&hspi2) != HAL_SPI_ERROR_NONE)
		return -1;
	else return 0;
}

