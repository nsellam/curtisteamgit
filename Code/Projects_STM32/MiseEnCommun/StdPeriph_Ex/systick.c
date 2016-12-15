/**
 * @file	systick.c
 * @author	Curtis Team
 * @brief	Functions to handle systick (STM internal time)  
 */

/* Includes ------------------------------------------------------------------*/
#include "systick.h"
#include "nvic.h"

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

/**
 * @brief     Makes the initialization of the systick system 
*/
void SysTick_QuickInit(void) {
  time_millis = 0;
    while (SysTick_Config(SystemCoreClock / SYSTICK_FREQ - 1) != 0);
    NVIC_QuickInit(SysTick_IRQn, 1);
}

/**
 * @brief     Returns the current STM32 time
 * @return     uint64_t (time elapsed since systick initialization expressed in milliseconds) 
*/
uint64_t millis(void) {
  return time_millis;
}

/**
 * @brief Callback associated to SysTick. Increments current time. 
*/
void SysTick_Callback(void) {
  time_millis++;
}

/* Private functions ---------------------------------------------------------*/
