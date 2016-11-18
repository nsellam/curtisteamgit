/**
 * @file CommunicationChecker.h
 * @author Curtis Team
 * @brief Handler of code to detect SPI errors
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
 *   SHARED VARIABLES   *
 ************************/

/**
 * @var int Time_Without_Message
 * @brief Elapsed time since last valid or invalid message (expressed in ms).
*/
uint8_t Time_Without_Message;

/**
 * @var int Number_Of_Invalid_Messages
 * @brief Number of consecutive invalid messages.
*/
uint8_t Number_Of_Invalid_Messages;

/**
 * @var uint8_t Error_MISO
 * @brief TRUE if MISO wire is unplegged, FALSE otherwise.
*/
uint8_t Error_MISO;

/**
 * @var uint8_t Error_MOSI
 * @brief TRUE if MOSI wire is unplegged, FALSE otherwise.
*/
uint8_t Error_MOSI; 

/**
 * @var uint8_t Error_CLK
 * @brief TRUE if CLK wire (SPI clock) is unplegged, FALSE otherwise.
*/
uint8_t Error_CLK; 
