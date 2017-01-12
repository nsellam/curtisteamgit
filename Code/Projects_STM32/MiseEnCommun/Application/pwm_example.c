#include <stdint.h>
#include <stm32f10x.h>

#include "pwm.h"

/**
 * @brief 	Sets PWM output on PA8 and its complementary on PB13. PWMs frequency is 1 kHz. Duty cycle on PA8 is 0.75.
 * @retval 	None
*/
void PWM_Example(void) {

    PWM_QuickInit(TIM1, TIM_Channel_1, 1000.0);         // Output on PA8
    //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
    PWM_QuickInit_Complementary(TIM1, TIM_Channel_1);   // Output on PB13
    
    PWM_SetDutyCycle(TIM1, TIM_Channel_1, 0.75);
    PWM_Start(TIM1);
}
