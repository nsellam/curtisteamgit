/**
 * @file    adc_example.c
 * @author  Curtis Team
 * @brief   ADC API use case example
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "adc.h"

#define ADCx ADC1
#define RANK 1
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
volatile uint16_t value;

/**
 * @brief 	Sets PA0 as analog input
 * @retval 	None
*/
void ADC_Example(void) {
    ADC_QuickInit(ADCx, GPIOA, GPIO_Pin_0, RANK, ADC_SampleTime_71Cycles5);
    
    while(1) {
        value = ADC_QuickGet(ADCx, RANK);
    }
}

/* Private functions ---------------------------------------------------------*/
