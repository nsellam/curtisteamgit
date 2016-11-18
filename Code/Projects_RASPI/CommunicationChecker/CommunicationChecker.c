/**
 * @file CommunicationChecker.c
 * @author Curtis Team
 * @brief Code to detect SPI errors
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

#include "data.h" 
#include "CommunicationChecker.h"
#include "SPI_errors.h"


/************************
 *      DEFINES         *
 ************************/

/**
 * @def MAX_TIME_WITHOUT_MESSAGE
 * @brief Max allowed time without receiving a message before declaring communication interrupted (expressed in ms). 
*/
#define MAX_TIME_WITHOUT_MESSAGE 10 //microseconds 

/**
 * @def MAX_UNREADABLE_MESSAGES
 * @brief Allowed consecutive received unreadable messages before declaring communication interrupted.
*/
#define MAX_UNREADABLE_MESSAGES 5 //# of messages


/************************
 *   SHARED VARIABLES   *
 ************************/

uint8_t Time_Without_Message = 0;
uint8_t Number_Of_Invalid_Messages = 0;
uint8_t Error_MISO = FALSE; 
uint8_t Error_MOSI = FALSE; 
uint8_t Error_CLK = FALSE; 


/************************
 *      MUTEX           *
 ************************/
 
pthread_mutex_t mutexTime_Without_Message;
pthread_mutex_t mutexNumber_Of_Invalid_Messages;


/************************
 *      THREADS         *
 ************************/

/**
 * @fn On_Message_Received
 * @brief Code which must be executed when an message (valid or not) is received 
 * This is a trigered function (on valid message read), it mission is to : 
 *	- reset Time_Without_Message
 * @param arg : unused -> void*
 * @return void* (unset)
*/
void* On_Message_Received (void *arg) {
	pthread_mutex_lock(&mutexTime_Without_Message);
	Time_Without_Message = 0; 
	pthread_mutex_unlock(&mutexTime_Without_Message);
}

/**
 * @fn On_Valid_Message
 * @brief Code which must be executed when an valid message is read 
 * This is a trigered function (on valid message read), it mission is to : 
 *	- reset Number_Of_Invalid_Messages 
 * @param arg : unused -> void*
 * @return void* (unset)
*/
void* On_Valid_Message (void *arg) {
	pthread_mutex_lock(&mutexNumber_Of_Invalid_Messages);
	Number_Of_Invalid_Messages = 0; 
	pthread_mutex_unlock(&mutexNumber_Of_Invalid_Messages);
}

/**
 * @fn On_Invalid_Message
 * @brief Code which must be executed when an unreadable message is read 
 * This is a trigered function (on invalid message read), it mission is to : 
 *	- update Number_Of_Invalid_Messages 
 * @param arg : unused -> void*
 * @return void* (unset)
*/
void* On_Invalid_Message (void *arg) {
	pthread_mutex_lock(&mutexNumber_Of_Invalid_Messages);
	Number_Of_Invalid_Messages ++; 
	pthread_mutex_unlock(&mutexNumber_Of_Invalid_Messages);
}

/**
 * @fn Communication_Checker
 * @brief Update Error_MISO and Error_CLK variables 
 * This a periodic function whose work is to detect when communication between Raspberry and Nucleo is broken. It also diagnose which wire has the most chances to be broken and update Error_MISO and Error_CLK variables consequently. Important : Raspberry can not detect a problem on MOSI wire.  
 * @param arg : unused -> void*
 * @return void* (unset)
*/
// TODO : fonction périodique toutes les 1 ms (???)
void* Communication_Checker(void *arg) {
	
	// Local variables declaration
	uint8_t localTime_Without_Message = -1;
	uint8_t localNumber_Of_Invalid_Messages = -1;
	
	pthread_mutex_lock(&mutexTime_Without_Message);
	localTime_Without_Message = Time_Without_Message; 
	pthread_mutex_unlock(&mutexTime_Without_Message);
	
	// Good variable reading checking
	// if (localTime_Without_Message == -1) ==> ERROR
	
	if (localTime_Without_Message > MAX_TIME_WITHOUT_MESSAGE) {
		set_error_CLK(TRUE); 
	}
	else {
		pthread_mutex_lock(&mutexNumber_Of_Invalid_Messages);
		localNumber_Of_Invalid_Messages = Number_Of_Invalid_Messages; 
		pthread_mutex_unlock(&mutexNumber_Of_Invalid_Messages);
		
		// Good variable reading checking
		// if (localNumber_Of_Invalid_Messages == -1) ==> ERROR
		
		if (localNumber_Of_Invalid_Messages > MAX_UNREADABLE_MESSAGES) {
			set_error_MISO(TRUE); 
		}
		else {
			pthread_mutex_lock(&mutexTime_Without_Message);
			Time_Without_Message ++; 
			pthread_mutex_unlock(&mutexTime_Without_Message);
		}
	}
}


uint8_t main (void) {

	/*======================= TASKS DECLARATION =====================*/
	pthread_t taskCommunication_Checker; 

	/*========================= TASKS CREATION ======================*/
	pthread_create(& taskCommunication_Checker, NULL, Communication_Checker, NULL);
	
	/*========================= TASKS JOINING =======================*/
	pthread_join(taskCommunication_Checker, NULL);
	
	return 0;
}
