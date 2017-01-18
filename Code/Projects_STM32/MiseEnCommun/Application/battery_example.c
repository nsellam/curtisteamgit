/**
 * @file    us_sensors.c
 * @author  Curtis Team
 * @brief   Battery API use case example
 */
 
/* Includes ------------------------------------------------------------------*/
#include "battery.h"
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
 * @brief   Prints continuously battery level
 * @retval  None
 */
void Battery_Example(void) {
    uint8_t percentageBattery;
    Battery_QuickInit();
    
    while(1) {
        percentageBattery = Battery_get();
        printf("%d %% \n", percentageBattery);
    }
}
/* Private functions ---------------------------------------------------------*/
