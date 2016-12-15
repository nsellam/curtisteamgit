/**
 * @file battery.c
 * @author Curtis Team
 * @brief Service function for getting the battery's level
 */
 
 /**
* @def _BATTERY_H_
* @brief to memorize if "battery.h" file has already been included
*/
#ifndef _BATTERY_H_
#define _BATTERY_H_

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stm32f10x_conf.h>

/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn Battery_GetLevel
* @brief Get the battery level in percentage
* @param GPIO_TypeDef*,GPIO_BATTERY; PIN_BATTERY: GPIO and Pin number for battery level use
* @param ADC_TypeDef*, ADC_BATTERY; ADC_BATTERY_CHANNEL; ADC_BATTERY_SAMPLE_TIME: ADC, the channel and its channel sample time for battery level use
* @return u8int_t Battery level in percentage
*/
uint8_t Battery_GetLevel(void);

#endif // _BATTERY_H_

