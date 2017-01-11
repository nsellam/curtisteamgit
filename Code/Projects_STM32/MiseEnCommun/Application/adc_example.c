#include <stdint.h>
#include <stm32f10x.h>

#include "adc.h"

/**
 * @brief 	Sets PA0 as analog input
 * @retval 	None
*/
void ADC_Example(void) {
    ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_0, 0, ADC_SampleTime_71Cycles5);
}
