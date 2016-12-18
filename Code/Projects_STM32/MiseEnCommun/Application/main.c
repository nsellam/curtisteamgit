#include <stdint.h>

#include <stm32f10x.h>

#include "pwm.h"
#include "adc.h"
#include "systick.h"
#include "spi.h"

void PWM_Example(void);
void ADC_Example(void);

int main (void) {
//    SysTick_QuickInit();
    
//    PWM_Example();
    
//    ADC_Example();

//    SPI_QuickInit(*SPI1, SPI_Mode_Slave);
    while (1) {}
}

/**
 * @brief 	Sets PWM output on PA8 and its complementary on PB13. PWMs frequency is 1 kHz. Duty cycle on PA8 is 0.75.
 * @retval 	None
*/
void PWM_Example(void) {
    PWM_QuickInit(TIM1, TIM_Channel_1, 1000.0);         // Output on PA8
    PWM_QuickInit_Complementary(TIM1, TIM_Channel_1);   // Output on PB13
    
    PWM_SetDutyCycle(TIM1, TIM_Channel_1, 0.75);
    PWM_Start(TIM1);
}

/**
 * @brief 	Sets PA0 as analog input
 * @retval 	None
*/
void ADC_Example(void) {
    ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_0, ADC_SampleTime_71Cycles5, 0);
}
