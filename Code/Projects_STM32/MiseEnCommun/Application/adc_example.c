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
/**
 * @brief   Name of the ADC pins 
 */
static const char * Pin_Names[ADC_NB_CHANNELS_MAX] = {
    "PA0", "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7",
    "PB0", "PB1", "PC0", "PC1", "PC2", "PC3", "PC4", "PC5"
};

/**
 * @brief   Port associated to each ADC pins 
 */
static GPIO_TypeDef * Port_List[ADC_NB_CHANNELS_MAX] = {
    GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA,
    GPIOB, GPIOB, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC
};

/**
 * @brief   Pin number associated to each ADC pins 
 */
static const uint16_t Pin_List[ADC_NB_CHANNELS_MAX] = {
    GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_7,
    GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5
};

/**
 * @brief   Values read on each ADC channel
 */
volatile uint16_t values[ADC_NB_CHANNELS_MAX];

/**
 * @brief   Corresponding voltage to values read on each ADC channel
 */
volatile float voltages[ADC_NB_CHANNELS_MAX];

/**
 * @brief   Condition of eah ADC Channel
 */
volatile uint8_t checked[ADC_NB_CHANNELS_MAX] = {0};

/* Private function prototypes -----------------------------------------------*/
float to_voltage(uint16_t value);
uint8_t check_voltage(float voltage);
void print_pin_voltage(int index);
void print_voltages(void);

/* Public functions ----------------------------------------------------------*/

/**
 * @brief 	Tests all the possible gpio pins as analog inputs for ADC1
 * Start the debugger and run the program.
 * To test the ADC pins:
 *    1) Connect every ADC pin (PA0..7, PB0..1, PC0..5) to the ground
 *    2) Connect every ADC pin (PA0..7, PB0..1, PC0..5) to the 3.3V
 * Display meaning:
 *    - 'OK' means the pin passed the test
 *    - '-'  means the pin did not pass the test (yet)
 * Two 'OK' means the pin is very likely to work.
 * Although this test is not 100% reliable, it is a good tool to detect a malfunctioning pin.
 * @retval  None
*/
void ADC_Example(void) {
    int i;
    int error = 0;
    
    // Initialize all the ADC pins
    for (i = 0; i < ADC_NB_CHANNELS_MAX; i++)
        if (ADC_QuickInit(ADC1, Port_List[i], Pin_List[i], i+1, ADC_SampleTime_41Cycles5) != ADC_NO_ERROR) error++;
    
    // Check if initialization is OK
    if (!error) {
        while (1) {
            // Test each channel
            for (i = 0; i < ADC_NB_CHANNELS_MAX; i++) {
                // Retrieve the raw converted value
                values[i] = ADC_QuickGet(ADC1, i+1);
                // Compute the voltage
                voltages[i] = to_voltage(values[i]);
                // Check if the voltage passed the ground or the 3.3V threshold test
                checked[i] |= check_voltage(voltages[i]);
            }
            // Display everything in the Debug Viewer
            print_voltages();
            // Delay
            dbg_sleep(100);
        }
    }
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Max admissible voltage on ADC pins
 */
#define V_MAX 3.3

/**
 * @brief   Convert the digital value given to the theoric voltage
 * @param   value A value given by an ADC
 * @retval  Theoric voltage
 */
float to_voltage(uint16_t value) {
    return V_MAX*(float)value/0xFFF;
}

/**
 * @brief   Acceptable delta on ADC pins
 */
#define V_MARGIN 0.1

/**
 * @brief   Check if voltage is in the expected interval
 * @param   voltage Voltage to check.
 * @retval  '1' if voltage is acceptable, '0' if not.
 */
uint8_t check_voltage(float voltage) {
    return (voltage <= 0.0 + V_MARGIN) | ((voltage >= V_MAX - V_MARGIN) << 1);
}

/**
 * @brief   Display function
 * @param   index Number of the ADC Channel to print
 * @retval  None
 */
void print_pin_voltage(int index) {
    printf("%s: %.2fV", Pin_Names[index], voltages[index]);
    printf("\t");
    if (checked[index] & 0x1) printf("OK"); else printf("-");
    printf("\t");
    if (checked[index] & 0x2) printf("OK"); else printf("-");
}

/**
 * @brief   Display function
 * @retval  None
 */
void print_voltages(void) {
    int i;
    printf("\t\tGND\t3.3V\t| \t\tGND\t3.3V\t\n");
    for(i = 0; i < ADC_NB_CHANNELS_MAX/2; i++) {
        print_pin_voltage(i); printf("\t| ");
        print_pin_voltage(i+8); printf("\n");
    }
    printf("\n");
}
