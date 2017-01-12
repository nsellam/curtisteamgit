#include <stdint.h>
#include <stm32f10x.h>

#include "adc.h"

#define ADCx ADC1
#define RANK 1

/**
 * @brief 	Sets PA0 as analog input
 * @retval 	None
*/
void ADC_Example(void) {
    volatile int value;
    
    ADC_QuickInit(ADCx, GPIOA, GPIO_Pin_0, RANK, ADC_SampleTime_71Cycles5);
    
    while(1) {
        value = ADC_QuickGet(ADCx, RANK);
    }
}
