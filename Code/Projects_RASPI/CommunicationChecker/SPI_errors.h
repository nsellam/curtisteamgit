/**
 * @file SPI_errors.h
 * @author Curtis Team
 * @brief Handler of handling function for variable SPI_errors
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
 *      DEFINES         *
 ************************/

/**
 * @def TRUE
 * @brief Used when uint_t are used as boolean
*/
#define TRUE 1

/**
 * @def FALSE
 * @brief Used when uint_t are used as boolean
*/
#define FALSE 0


/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn set_errors_SPI
 * @brief Set all errors of errors_SPI to given state. For initialisationn and debug only. 
 * @return void
 * @param Error_CLK -> uint8_t
 * @param Error_MISO -> uint8_t
 * @param Error_MOSI -> uint8_t
*/
void set_errors_SPI (uint8_t Error_CLK, uint8_t Error_MISO, uint8_t Error_MOSI);

/**
 * @fn set_error_CLK
 * @brief Set error_CLK according the value of argument Error. error_CLK bit from shared variable errors_SPI, is set to 0 (FALSE) if parameter is 0 and set to 1 (TRUE) if not. 
 * @return void
 * @param Error -> uint8_t
*/
void set_error_CLK (uint8_t Error);

/**
 * @fn set_error_MISO
 * @brief Set error_MISO according the value of argument Error. error_MISO bit from shared variable errors_SPI, is set to 0 (FALSE) if parameter is 0 and set to 1 (TRUE) if not. 
 * @param Error -> uint8_t
 * @return void
*/
void set_error_MISO (uint8_t Error);

/**
 * @fn set_error_MOSI
 * @brief Set error_MOSI according the value of argument Error. error_MOSI bit from shared variable errors_SPI, is set to 0 (FALSE) if parameter is 0 and set to 1 (TRUE) if not. 
 * NOT SUPPOSED TO BE USED ON RASPBERRY PI FINAL CODE 
 * @param Error -> uint8_t
 * @return void
*/
void set_error_MOSI (uint8_t Error);

/**
 * @fn get_error_CLK
 * @brief Return error_CLK (part of erros_SPI) state
 * @return uint8_t : 1 (TRUE) if error_CLK == 1, 0 (FALSE) if not
*/
uint8_t get_error_CLK (void);

/**
 * @fn get_error_MISO
 * @brief Return error_MISO (part of erros_SPI) state
 * @return uint8_t : 1 (TRUE) if error_MISO == 1, 0 (FALSE) if not
*/
uint8_t get_error_MISO (void);

/**
 * @fn get_error_MOSI
 * @brief Return error_MOSI (part of erros_SPI) state
 * @return uint8_t : 1 (TRUE) if error_MOSI == 1, 0 (FALSE) if not
*/
uint8_t get_error_MOSI (void);
