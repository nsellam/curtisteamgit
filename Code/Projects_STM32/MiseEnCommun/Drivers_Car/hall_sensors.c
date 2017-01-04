/**
 * @file    hall_sensors.c
 * @author  Curtis Team
 * @brief   Functions to handle hall sensors  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "hall_sensors.h"
#include "exti.h"
#include "system_time.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief Value to be add to variables at each front when count. 
*/
#define COUNT_ADDER         1 

/**
 * @brief Value to be add to variables at each front when decount. 
*/
#define DECOUNT_ADDER       -1

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/**
 * @brief Number of the hall detection. Positive is counted on rising edges, negative if not.  
*/
int32_t HallSensor_number_of_pop[HALL_SENSOR_NUMBER];

/**
 * @brief Date of the last dectections of each hall sensor
*/
uint64_t HallSensor_last_pops[HALL_SENSOR_MAX_SAVED_POP][HALL_SENSOR_NUMBER];

/**
 * @brief Number of the sector currently seen by each hall sensor
*/
uint16_t HallSensor_sector[HALL_SENSOR_NUMBER];

/**
 * @brief Number of laps count by each hall sensor. Positive is counted on rising edges, negative if not. 
*/
int32_t HallSensor_lap[HALL_SENSOR_NUMBER];

/**
 * @brief Number of ticks count during this periode
*/
int8_t HallSensor_current_periode_ticks[HALL_SENSOR_NUMBER];

/**
 * @brief Number of ticks count during the last periode
*/
int8_t HallSensor_periode_ticks[HALL_SENSOR_NUMBER];

/**
 * @brief Increment per front
*/
int8_t adder = COUNT_ADDER;

/* Private function prototypes -----------------------------------------------*/
void HallSensor_reset (uint8_t hall_identifier);
void HallSensor_newFront(uint8_t hall_identifier);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief       Reset and start specified hall sensor 
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R
 * @retval      None
*/
void HallSensor_init(uint8_t hall_identifier) {
	HallSensor_reset(hall_identifier);
	HallSensor_count(hall_identifier);
}

/**
 * @brief       Parameterizes hall sensor as counter
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R
 * @retval      None
*/
void HallSensor_count(uint8_t hall_identifier) {
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	
	if (hall_identifier == HALL_IDENTIFIER_L) {
		GPIO = HALL_SENSOR_L_GPIO;
		pin = HALL_SENSOR_L_PIN;
	}
	else if (hall_identifier == HALL_IDENTIFIER_R) {
		GPIO = HALL_SENSOR_R_GPIO;
		pin = HALL_SENSOR_R_PIN;
	}
	else {return;}	
	
	EXTI_QuickInit(GPIO, pin, HALL_SENSOR_TRIGG_FW, HALL_SENSOR_PRIO);
    
    adder = COUNT_ADDER;
}

/**
 * @brief       Parameterizes hall sensor as decounter
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R
 * @retval      None
*/
void HallSensor_decount(uint8_t hall_identifier) {
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	
	if (hall_identifier == HALL_IDENTIFIER_L) {
		GPIO = HALL_SENSOR_L_GPIO;
		pin = HALL_SENSOR_L_PIN;
	}
	else if (hall_identifier == HALL_IDENTIFIER_R) {
		GPIO = HALL_SENSOR_R_GPIO;
		pin = HALL_SENSOR_R_PIN;
	}
	else {return;}	
	
	EXTI_QuickInit(GPIO, pin, HALL_SENSOR_TRIGG_BW, HALL_SENSOR_PRIO);
    
    adder = DECOUNT_ADDER;
}
/**
 * @brief       Called function on external interrupt (EXTI). Must not be call by user. 
 * @param       hall_identifier : hall sensor on wich front was detected. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R
*/
void HallSensor_Callback(uint8_t hall_identifier) {
	HallSensor_newFront(hall_identifier);
}

/**
 * @brief       Returns the current sector for hall sensor considered.
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R.
 * @retval      Current sector if current sector is under number of sectors, ERROR_SENSOR_OUT_OF_RANGE if not.
*/
uint16_t HallSensor_getSector(uint8_t hall_identifier){
	if (HallSensor_sector[hall_identifier] >= HALL_SENSOR_NUMBER_OF_SECTORS) return ERROR_SENSOR_OUT_OF_RANGE; else {};
	return HallSensor_sector[hall_identifier];
}

/**
 * @brief       Returns the current lap for the hall sensor considered.
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R.
 * @retval      Curent lap.
*/
int32_t HallSensor_getLap(uint8_t hall_identifier) {
	return HallSensor_lap[hall_identifier];
}

/**
 * @brief       Returns the date (in milliseconds) of the last - n detection of the hall sensor. 
 * @param       n Number of the wanted sample.
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R.
 * @retval      uint64_t Time of the detection passed as parameter if it is possible to found it, ERROR_VALUE_NOT_FOUND if not.
*/
uint64_t HallSensor_getLastPop(uint8_t n, uint8_t hall_identifier) {
	int position_to_read = HallSensor_number_of_pop[hall_identifier] - n;
	
	if (n > HALL_SENSOR_MAX_SAVED_POP) return ERROR_VALUE_NOT_FOUND;  else {}; 

	if (position_to_read < 0) position_to_read = position_to_read + HALL_SENSOR_MAX_SAVED_POP; // TODO : verifier ce calcul et le commenter
		
	return HallSensor_last_pops[position_to_read][hall_identifier];
}

/**
 * @brief       Update local variable HallSensor_periode_ticks[] with the number of ticks counted during completed period
 * @retval      None
*/
void HallSensor_countPeridodTicks(void) {
	int i = 0; 
	for (i=0; i<HALL_SENSOR_NUMBER; i++) {
		HallSensor_periode_ticks[i] = HallSensor_current_periode_ticks[i];
		HallSensor_current_periode_ticks[i] = 0;
	}
}

/**
 * @brief       Return the number of ticks detected during the last hall sensor period
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R
 * @retval      uint8_t Number of ticks during previous period for the hall sensor considered
*/
int8_t HallSensor_getNumberTicksInPeriod(uint8_t hall_identifier) {
	return HallSensor_periode_ticks[hall_identifier];
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief       Reset all the variables used to describe a hall_sensor
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R.
 * @retval      None
*/
void HallSensor_reset (uint8_t hall_identifier) {
    	int i = 0;
	HallSensor_number_of_pop[hall_identifier] = 0;
	HallSensor_sector[hall_identifier] = 0;
	HallSensor_lap[hall_identifier] = 0;
	for (i = 0; i < HALL_SENSOR_MAX_SAVED_POP; i++)	{
		HallSensor_last_pops[i][hall_identifier] = 0;
	}
	HallSensor_periode_ticks[hall_identifier] = 0;
	HallSensor_current_periode_ticks[hall_identifier] = 0;
	//callbacks_services_reset_time_to_next_hall_period();
}

/**
 * @brief       Updates the hall sensor definied variables according to . 
 * @param       hall_identifier Number of the hall sensor to consider. It's recommended to use identifier such HALL_IDENTIFIER_L or HALL_IDENTIFIER_R.
 * @retval      None
*/
void HallSensor_newFront(uint8_t hall_identifier) {
	HallSensor_last_pops[HallSensor_number_of_pop[hall_identifier]][hall_identifier] = millis();
	
	HallSensor_number_of_pop[hall_identifier] ++;
	if (HallSensor_number_of_pop[hall_identifier] >= HALL_SENSOR_MAX_SAVED_POP) HallSensor_number_of_pop[hall_identifier] = 0; else {} 
	
	HallSensor_sector[hall_identifier] = HallSensor_sector[hall_identifier] + adder;
	
	if (HallSensor_sector[hall_identifier] == (uint16_t)(-1)) {
		HallSensor_sector[hall_identifier] = HALL_SENSOR_NUMBER_OF_SECTORS - 1; 
		HallSensor_lap[hall_identifier] --;
	}
	
	else if (HallSensor_sector[hall_identifier] >= HALL_SENSOR_NUMBER_OF_SECTORS) {
		HallSensor_sector[hall_identifier] = 0; 
		HallSensor_lap[hall_identifier] ++;
	}
	else {}
	HallSensor_current_periode_ticks[hall_identifier] = HallSensor_current_periode_ticks[hall_identifier] + adder;
}
