/**
 * @file    hall_sensors.c
 * @author  Curtis Team
 * @brief   Functions to handle hall sensors  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "hall_sensors.h"
#include "exti.h"
#include "system_time.h"
#include "driver_callbacks.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief Value to be add to variables at each edge when count. 
*/
#define COUNT_ADDER         1 

/**
 * @brief Value to be add to variables at each edge when decount. 
*/
#define DECOUNT_ADDER       -1

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/**
 * @brief Number of the hall detection. Positive is counted on rising edges, negative if not.  
*/
int32_t HallSensor_numberOfPop[HALLSENSOR_NUMBER];

/**
 * @brief Date of the last dectections of each hall sensor
*/
uint64_t HallSensor_lastPops[HALLSENSOR_MAX_SAVED_POP][HALLSENSOR_NUMBER];

/**
 * @brief Number of the sector currently seen by each hall sensor
*/
uint16_t HallSensor_sector[HALLSENSOR_NUMBER];

/**
 * @brief Number of laps count by each hall sensor. Positive is counted on rising edges, negative if not. 
*/
int32_t HallSensor_lap[HALLSENSOR_NUMBER];

/**
 * @brief Number of ticks count during this periode
*/
int8_t HallSensor_currentPeriodeTicks[HALLSENSOR_NUMBER];

/**
 * @brief Number of ticks count during the last periode
*/
int8_t HallSensor_periodeTicks[HALLSENSOR_NUMBER];

/**
 * @brief Increment per edge
*/
int8_t adder = COUNT_ADDER;

/**
 * @brief Number of systick iteruptions to wait until next hall sensor period
*/
uint32_t HallSensor_remainingTimeInHallPeriod = HALLSENSOR_TIME_BETWEEN_TWO_UPDATES; 

/* Private function prototypes -----------------------------------------------*/
void HallSensor_reset (HallSensors_Enum hall_identifier);
void HallSensor_newEdge(HallSensors_Enum hall_identifier);
void HallSensor_resetTimeToNextHallPeriod(void);
void HallSensor_countPeridodTicks(void);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief       Reset and start specified hall sensor 
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      None
*/
void HallSensor_QuickInit(HallSensors_Enum hall_identifier) {
	HallSensor_reset(hall_identifier);
	HallSensor_count(hall_identifier);
}

/**
 * @brief       Parameterizes hall sensor as counter
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      None
*/
void HallSensor_count(HallSensors_Enum hall_identifier) {
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	
	if (hall_identifier == HALLSENSOR_L) {
		GPIO = HALLSENSOR_L_GPIO;
		pin = HALLSENSOR_L_PIN;
	}
	else if (hall_identifier == HALLSENSOR_R) {
		GPIO = HALLSENSOR_R_GPIO;
		pin = HALLSENSOR_R_PIN;
	}
	else {return;}	
	
	EXTI_QuickInit(GPIO, pin, HALLSENSOR_TRIGG_FW, HALLSENSOR_PRIO);
    
    adder = COUNT_ADDER;
}

/**
 * @brief       Parameterizes hall sensor as decounter
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      None
*/
void HallSensor_decount(HallSensors_Enum hall_identifier) {
	GPIO_TypeDef *GPIO;
	uint16_t pin;
	
	if (hall_identifier == HALLSENSOR_L) {
		GPIO = HALLSENSOR_L_GPIO;
		pin = HALLSENSOR_L_PIN;
	}
	else if (hall_identifier == HALLSENSOR_R) {
		GPIO = HALLSENSOR_R_GPIO;
		pin = HALLSENSOR_R_PIN;
	}
	else {return;}	
	
	EXTI_QuickInit(GPIO, pin, HALLSENSOR_TRIGG_BW, HALLSENSOR_PRIO);
    
    adder = DECOUNT_ADDER;
}
/**
 * @brief       Called function on external interrupt (EXTI). Must not be call by user. 
 * @param       hall_identifier : hall sensor on wich edge was detected. 
*/
void HallSensor_EdgeCallback(HallSensors_Enum hall_identifier) {
	HallSensor_newEdge(hall_identifier);
}

/**
 * @brief       Returns the current sector for hall sensor considered.
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      Current sector if current sector is under number of sectors, ERROR_SENSOR_OUT_OF_RANGE if not.
*/
uint16_t HallSensor_getSector(HallSensors_Enum hall_identifier){
	if (HallSensor_sector[hall_identifier] >= HALLSENSOR_NUMBER_OF_SECTORS) return ERROR_SENSOR_OUT_OF_RANGE; else {};
	return HallSensor_sector[hall_identifier];
}

/**
 * @brief       Returns the current lap for the hall sensor considered.
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      Curent lap.
*/
int32_t HallSensor_getLap(HallSensors_Enum hall_identifier) {
	return HallSensor_lap[hall_identifier];
}

/**
 * @brief       Returns the date (in milliseconds) of the last - n detection of the hall sensor. 
 * @param       n Number of the wanted sample.
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      uint64_t Time of the detection passed as parameter if it is possible to found it, ERROR_VALUE_NOT_FOUND if not.
*/
uint64_t HallSensor_getLastPop(uint8_t n, HallSensors_Enum hall_identifier) {
	int position_to_read = HallSensor_numberOfPop[hall_identifier] - n;
	
	if (n > HALLSENSOR_MAX_SAVED_POP) return ERROR_VALUE_NOT_FOUND;  else {}; 

	if (position_to_read < 0) position_to_read = position_to_read + HALLSENSOR_MAX_SAVED_POP; // TODO : verifier ce calcul et le commenter
		
	return HallSensor_lastPops[position_to_read][hall_identifier];
}

/**
 * @brief       Return the number of ticks detected during the last hall sensor period
 * @param       hall_identifier Number of the hall sensor to consider. 
 * @retval      uint8_t Number of ticks during previous period for the hall sensor considered
*/
int8_t HallSensor_getNumberTicksInPeriod(HallSensors_Enum hall_identifier) {
	return HallSensor_periodeTicks[hall_identifier];
}


void HallSensor_TimeCallback(void) {
    HallSensor_remainingTimeInHallPeriod --; 
	if (HallSensor_remainingTimeInHallPeriod == 0) {
		HallSensor_countPeridodTicks();
		HallSensor_resetTimeToNextHallPeriod();
	}
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief       Reset all the variables used to describe a hall_sensor.
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      None
*/
void HallSensor_reset (HallSensors_Enum hall_identifier) {
    int i = 0;
	HallSensor_numberOfPop[hall_identifier] = 0;
	HallSensor_sector[hall_identifier] = 0;
	HallSensor_lap[hall_identifier] = 0;
	for (i = 0; i < HALLSENSOR_MAX_SAVED_POP; i++)	{
		HallSensor_lastPops[i][hall_identifier] = 0;
	}
	HallSensor_periodeTicks[hall_identifier] = 0;
	HallSensor_currentPeriodeTicks[hall_identifier] = 0;
    HallSensor_resetTimeToNextHallPeriod();
}

/**
 * @brief       Updates the hall sensor definied variables according to hall sensor specified. 
 * @param       hall_identifier Number of the hall sensor to consider.
 * @retval      None
*/
void HallSensor_newEdge(HallSensors_Enum hall_identifier) {
	HallSensor_lastPops[HallSensor_numberOfPop[hall_identifier]][hall_identifier] = millis();
	
	HallSensor_numberOfPop[hall_identifier] ++;
	if (HallSensor_numberOfPop[hall_identifier] >= HALLSENSOR_MAX_SAVED_POP) HallSensor_numberOfPop[hall_identifier] = 0; else {} 
	
	HallSensor_sector[hall_identifier] = HallSensor_sector[hall_identifier] + adder;
	
	if (HallSensor_sector[hall_identifier] == (uint16_t)(-1)) {
		HallSensor_sector[hall_identifier] = HALLSENSOR_NUMBER_OF_SECTORS - 1; 
		HallSensor_lap[hall_identifier] --;
	}
	
	else if (HallSensor_sector[hall_identifier] >= HALLSENSOR_NUMBER_OF_SECTORS) {
		HallSensor_sector[hall_identifier] = 0; 
		HallSensor_lap[hall_identifier] ++;
	}
	else {}
	HallSensor_currentPeriodeTicks[hall_identifier] = HallSensor_currentPeriodeTicks[hall_identifier] + adder;
}

/**
 * @brief       Reinit private variable indicating time remainng before the next hall sensor period.
 * @retval      None
*/
void HallSensor_resetTimeToNextHallPeriod(void) {
    HallSensor_remainingTimeInHallPeriod = HALLSENSOR_TIME_BETWEEN_TWO_UPDATES; 
}

/**
 * @brief       Update local variable HallSensor_periodeTicks[] with the number of ticks counted during completed period.
 * @retval      None
*/
void HallSensor_countPeridodTicks(void) {
	int i = 0; 
	for (i=0; i<HALLSENSOR_NUMBER; i++) {
		HallSensor_periodeTicks[i] = HallSensor_currentPeriodeTicks[i];
		HallSensor_currentPeriodeTicks[i] = 0;
	}
}
