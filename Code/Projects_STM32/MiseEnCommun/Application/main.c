#include <stdint.h>

#include <stm32f10x.h>

#include "pwm.h"

int PWM_Example(void);

int main(void) {
    
    PWM_Example();
    
    while (1) {}
}

/**
 * @brief 	Sets PWM output on PA8 and its complementary on PB13
 * @retval 	None
*/
int PWM_Example(void) {
    
    PWM_QuickInit(TIM1, TIM_Channel_1, 1000.0);         // Output on PA8
    PWM_QuickInit_Complementary(TIM1, TIM_Channel_1);   // Output on PB13
    
    PWM_SetDutyCycle(TIM1, TIM_Channel_1, 0.75);
    PWM_Start(TIM1);
        
    return 0;
}

