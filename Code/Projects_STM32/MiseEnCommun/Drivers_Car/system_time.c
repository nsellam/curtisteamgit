/**
 * @file    system_time.c
 * @author  Curtis Team
 * @brief   Functions to manage time  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "system_time.h"
#include "systick.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
 * @brief     Current STM32 time (expressed in milliseconds)
*/
static uint64_t time_millis;

/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

__weak void HallSensor_TimeCallback(void) {}
__weak void Manager_Callback(void) {}

/**
 * @brief       Makes the initialization of time for the whole system 
 * @retval      None
*/
void System_Time_QuickInit(void) {
    time_millis = 0;
    SysTick_QuickInit();
}

/**
 * @brief       Callback associated to SysTick. 
 * Please add here your periodic functions
 * @retval      None
*/
void SysTick_Callback(void) {
    // Time increment 
    time_millis ++;
    
    HallSensor_TimeCallback();
    Manager_Callback();
    // Other periodic functions (every 1 ms)
    
    // Other periodic functions (every 10 ms)
    //if (time_millis % 10 == 0) {}
    
    // Other periodic functions (every 100 ms)
    //if (time_millis % 100 == 0) {}
    
    // Other periodic functions (every 1 s)
    //if (time_millis % 1000 == 0) {}
    
}

/**
 * @brief       Returns the current STM32 time
 * @return      uint64_t Time elapsed since initialization 
 * @retval      Result is expressed in ms 
*/
uint64_t millis(void) {
  return time_millis;
}

/**
 * @brief       Pauses the system during the specified time
 * @param       ms Expected pause length (expressed in milliseconds)
 * @retval      None
*/
void pause(uint16_t ms) {
    uint64_t arrivalTime = time_millis;
    while (time_millis < arrivalTime + ms) {
    }
}

/* Private functions ---------------------------------------------------------*/
