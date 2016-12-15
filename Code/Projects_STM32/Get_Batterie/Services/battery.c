/**
 * @file battery.c
 * @author Curtis Team
 * @brief Service function for getting the battery's level
 */
 
 /********************************/
/*       LIBRARIES              */
/********************************/
#include "battery.h"
#include "adc.h"
#include "stm32f10x_conf.h"

/********************************/
/*         CONSTANTS            */
/********************************/

/**
* @def GPIO_BATTERY
* @brief Define the GPIO for getting battery level: GPIOB
*/
#define GPIO_BATTERY GPIOB

/**
* @def PIN_BATTERY
* @brief Define the GPIO Pin number for getting battery level: Pin0 (PB0)
*/
#define PIN_BATTERY GPIO_Pin_0

/**
* @def ADC_BATTERY
* @brief Define the ADC for getting battery level: ADC2
*/
#define ADC_BATTERY ADC2

/**
* @def ADC_BATTERY_CHANNEL
* @brief Define the ADC Channel for getting battery level: ADC2 Channel 8
*/
#define ADC_BATTERY_CHANNEL ADC_Channel_8

/**
* @def ADC_BATTERY_SAMPLE_TIME
* @brief Define the ADC Sample Time for getting battery level
*/
#define ADC_BATTERY_SAMPLE_TIME ADC_SampleTime_7Cycles5

/**
* @def PERCENTAGE
* @brief Convert float to percentage coefficient 
*/
#define PERCENTAGE 100

/**
* @def ADC_SCALE
* @brief ADC scale for calculating the battery level value : 4069/3.3 *(3.2 - 1.6) = 1973 = 0x07B5
*/
#define ADC_SCALE ((uint16_t)0x07B5) //1973

/**
* @var Battery_ADC_Value
* @brief Intermediate battery value in ADC register coded in 12 bits
*/
uint16_t Battery_ADC_Value;

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
uint8_t Battery_GetLevel(void){
	//init adc for battery use: on GPIO PB8, ADC2 channel 8
	Init_ADC_One_Channel (GPIO_BATTERY, PIN_BATTERY, ADC_BATTERY, ADC_BATTERY_CHANNEL, ADC_BATTERY_SAMPLE_TIME);
    Battery_ADC_Value = ADC_Single_Channel_Value(ADC_BATTERY);
	return PERCENTAGE*(Battery_ADC_Value - ADC_SCALE)/ADC_SCALE;
}
