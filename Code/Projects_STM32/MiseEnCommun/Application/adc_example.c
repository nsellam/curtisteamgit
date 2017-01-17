/**
 * @file    adc_example.c
 * @author  Curtis Team
 * @brief   ADC API use case example
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stm32f10x.h>
#include "adc.h"
#include "debug.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static const char * pin_names[ADC_NB_CHANNELS_MAX] = {
    "PA0", "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7",
    "PB0", "PB1", "PC0", "PC1", "PC2", "PC3", "PC4", "PC5"
};

volatile uint16_t values[ADC_NB_CHANNELS_MAX];
volatile float voltages[ADC_NB_CHANNELS_MAX];
volatile char checked[ADC_NB_CHANNELS_MAX] = {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'};

/* Private function prototypes -----------------------------------------------*/
void sleep(void);

float to_voltage(int index);
char check_voltage(int index);
void print_pin_voltage(int index);
void print_voltages(void);

/* Public functions ----------------------------------------------------------*/

/**
 * @brief 	Tests all the possible gpio pins as analog inputs for ADC1
 * Start the debugger
 * To test the ADC pins:
 *    1) Connect every ADC pin (PA0..7, PB0..1, PC0..5) to the ground
 *    2) Connect every ADC pin (PA0..7, PB0..1, PC0..5) to the 3.3V
 * Display meaning:
 *    - 'OK' means the pin works
 *    - '+'  means the pin passed the 3.3V test step
 *    - '-'  means the pin passed the ground test step
 *    - 'X'  means the pin did not pass any test
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
    
    if (!error) {
        while(1) {
            for(i = 0; i < ADC_NB_CHANNELS_MAX; i++) {
                values[i] = ADC_QuickGet(ADC1, i+1);
                voltages[i] = to_voltage(i);
                checked[i] = check_voltage(i);
            }
            print_voltages();
            sleep();
        }
    }
}

/* Private functions ---------------------------------------------------------*/

void sleep(void) {
    int i;
    for(i = 0; i < 2e5; i++);
}

#define V_MAX 3.3
float to_voltage(int index) {
    return V_MAX*(float)values[index]/0xFFF;
}

#define V_MARGIN 0.1
char check_voltage(int index) {
    if (voltages[index] >= V_MAX - V_MARGIN) {
        if (checked[index] == 'X')
            return '+';
        else if (checked[index] == '-')
            return ' ';
    } else if (voltages[index] <= 0.0 + V_MARGIN) {
        if (checked[index] == 'X')
            return '-';
        else if (checked[index] == '+')
            return ' ';
    }
    return checked[index];
}

void print_pin_voltage(int index) {
    printf("%s: %.2f %c", pin_names[index], voltages[index], checked[index]);
    if (checked[index] == ' ') printf("OK");
}

void print_voltages(void) {
    int i;
    for(i = 0; i < ADC_NB_CHANNELS_MAX/2; i++) {
        print_pin_voltage(i); printf("\t");
        print_pin_voltage(i+8); printf("\n");
    }
    printf("\n");
}
