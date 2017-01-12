/**
 * @file    adc_example.c
 * @author  Curtis Team
 * @brief   ADC API use case example
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "adc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief 	ADC to test
*/
#define ADCx            ADC1

/**
 * @brief 	Rank in the ADC sequence of the measure to consider
*/
#define RANK            1

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
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

/* Private functions ---------------------------------------------------------*/
