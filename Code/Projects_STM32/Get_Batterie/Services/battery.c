#include "battery.h"
#include "adc.h"
#include "stm32f10x_conf.h"
//#include "stm32f10x_it.h"


#define GPIO_BATTERY GPIOB
#define PIN_BATTERY GPIO_Pin_0
#define ADC_BATTERY ADC2
#define ADC_BATTERY_CHANNEL ADC_Channel_8
#define ADC_BATTERY_SAMPLE_TIME ADC_SampleTime_7Cycles5
#define DMA_BATTERY DMA1_Channel1
#define PERCENTAGE 100
#define ADC_SCALE ((uint16_t)0x07B5) //1973


uint16_t Battery_ADC_Value;

uint8_t Battery_GetLevel(void){
	//init adc for battery use: on GPIO PB8, ADC2 channel 8
	Init_ADC_One_Channel (GPIO_BATTERY, PIN_BATTERY, ADC_BATTERY, ADC_BATTERY_CHANNEL, ADC_BATTERY_SAMPLE_TIME);
    Battery_ADC_Value = ADC_Single_Channel_Value(ADC_BATTERY);
	return PERCENTAGE*(Battery_ADC_Value - ADC_SCALE)/ADC_SCALE;
}
