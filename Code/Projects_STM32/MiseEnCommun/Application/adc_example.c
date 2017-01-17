/**
 * @file    adc_example.c
 * @author  Curtis Team
 * @brief   ADC API use case example
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>
#include "adc.h"
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void print_values(void);

/* Public functions ----------------------------------------------------------*/
volatile uint16_t values[16];

/**
 * @brief 	Sets all the possible gpio pins as analog inputs for ADC1
 * @retval 	None
*/
void ADC_Example(void) {
    int i;
    int error = 0;
    
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_0,  1, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_1,  2, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_2,  3, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_3,  4, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_4,  5, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_5,  6, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_6,  7, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_7,  8, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOB, GPIO_Pin_0,  9, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOB, GPIO_Pin_1, 10, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOC, GPIO_Pin_0, 11, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOC, GPIO_Pin_1, 12, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOC, GPIO_Pin_2, 13, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOC, GPIO_Pin_3, 14, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOC, GPIO_Pin_4, 15, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    if (ADC_QuickInit(ADC1, GPIOC, GPIO_Pin_5, 16, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    
    while(!error) {
        for(i = 0; i < 16; i++) {
            values[i] = ADC_QuickGet(ADC1, i+1);
        }
        print_values();
        for(i = 0; i < 2e5; i++);
    }
}

/* Private functions ---------------------------------------------------------*/

void print_values(void) {
    int i;
    for(i = 0; i < 8; i++) {
        printf("Rank %2d: %.2f\t", i, 3.3*(float)values[i]/0xFFF);
        printf("Rank %2d: %.2f\n", i+8, 3.3*(float)values[i+8]/0xFFF);
    }
    printf("\n");
}
