/**
 * @file SPI_errors.c
 * @author Curtis Team
 * @brief Code to handle variable SPI_errors
 */

/************************
 *      LIBRARIES       *
 ************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>


/************************
 *       HEADERS        *
 ************************/

#include "SPI_errors.h"
#include "data.h"


/************************
 *      DEFINES         *
 ************************/

/**
 * @def MASK_ERROR_CLK
 * @brief Mask used to access to error_CLK value in errors_SPI variable. 
*/
#define MASK_ERROR_CLK 1  // b 0000 0001

/**
 * @def MASK_ERROR_MISO
 * @brief Mask used to access to error_MISO value in errors_SPI variable. 
*/
#define MASK_ERROR_MISO 2 // b 0000 0010

/**
 * @def MASK_ERROR_MOSI
 * @brief Mask used to access to error_MOSI value in errors_SPI variable. 
*/
#define MASK_ERROR_MOSI 4 // b 0000 0100


/************************
 *      FUNCTIONS       *
 ************************/

pthread_mutex_t mutexdata;  // TODO : a mettre dans data.h

void set_errors_SPI (uint8_t Error_CLK, uint8_t Error_MISO, uint8_t Error_MOSI) {
	uint8_t new_errors_SPI = 0; // b 0000 0000
	if (Error_CLK) {
		new_errors_SPI = new_errors_SPI | MASK_ERROR_CLK;
	} 
	else {} 
	
	if (Error_MISO) {
		new_errors_SPI = new_errors_SPI | MASK_ERROR_MISO;
	} 
	else {} 
	
	if (Error_MOSI) {
		new_errors_SPI = new_errors_SPI | MASK_ERROR_MOSI;
	} 
	else {} 
		
	pthread_mutex_lock(&mutexDataSTM);
	pdata->data_STM.errors_SPI = new_errors_SPI;
	pthread_mutex_unlock(&mutexDataSTM);
}


void set_error_CLK (uint8_t Error) {
	if (! Error) {
		pthread_mutex_lock(&mutexDataSTM);
		pdata->data_STM.errors_SPI = pdata->data_STM.errors_SPI | MASK_ERROR_CLK;
		pthread_mutex_unlock(&mutexDataSTM);
	}
	else {
		pthread_mutex_lock(&mutexDataSTM);
		pdata->data_STM.errors_SPI = pdata->data_STM.errors_SPI & ~(MASK_ERROR_CLK) ;
		pthread_mutex_unlock(&mutexDataSTM);
	}
}


void set_error_MISO (uint8_t Error) {
	if (! Error) {
		pthread_mutex_lock(&mutexDataSTM);
		pdata->data_STM.errors_SPI = pdata->data_STM.errors_SPI | MASK_ERROR_MISO;
		pthread_mutex_unlock(&mutexDataSTM);
	}
	else {
		pthread_mutex_lock(&mutexDataSTM);
		pdata->data_STM.errors_SPI = pdata->data_STM.errors_SPI & ~(MASK_ERROR_MISO) ;
		pthread_mutex_unlock(&mutexDataSTM);
	}
}


void set_error_MOSI (uint8_t Error) {
	if (! Error) {
		pthread_mutex_lock(&mutexDataSTM);
		pdata->data_STM.errors_SPI = pdata->data_STM.errors_SPI | MASK_ERROR_MOSI;
		pthread_mutex_unlock(&mutexDataSTM);
	}
	else {
		pthread_mutex_lock(&mutexDataSTM);
		pdata->data_STM.errors_SPI = pdata->data_STM.errors_SPI & ~(MASK_ERROR_MOSI) ;
		pthread_mutex_unlock(&mutexDataSTM);
	}
}

uint8_t get_error_CLK (void) {
	uint8_t R = TRUE;
	uint8_t localerrors_SPI = 255; //b 1111 1111
	
	pthread_mutex_lock(&mutexDataSTM);
	localerrors_SPI = pdata->data_STM.errors_SPI;
	pthread_mutex_unlock(&mutexDataSTM);	

	R = (localerrors_SPI & MASK_ERROR_CLK);

	return R;
}


uint8_t get_error_MISO (void) {
	uint8_t R = TRUE;
	uint8_t localerrors_SPI = 255; //b 1111 1111
	
	pthread_mutex_lock(&mutexDataSTM);
	localerrors_SPI = pdata->data_STM.errors_SPI;
	pthread_mutex_unlock(&mutexDataSTM); 
	
	R = (localerrors_SPI & MASK_ERROR_MISO);
	
	return R;
}


uint8_t get_error_MOSI (void) {
	uint8_t R = TRUE;
	uint8_t localerrors_SPI = 255; //b 1111 1111
	
	pthread_mutex_lock(&mutexDataSTM);
	localerrors_SPI = pdata->data_STM.errors_SPI;
	pthread_mutex_unlock(&mutexDataSTM); 
		
	R = (localerrors_SPI & MASK_ERROR_MOSI);
	
	return R;
}

