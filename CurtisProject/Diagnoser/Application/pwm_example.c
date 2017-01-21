/**
 * @file    pwm_example.c
 * @author  Curtis Team
 * @brief   PWM API use case example
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "pwm.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief 	Sets PWM output on PA8 and its complementary on PB13. PWMs frequency is 1 kHz. Duty cycle on PA8 is 0.75.
 * @retval 	None
*/
void PWM_Diagnoser(void) {

    PWM_QuickInit(TIM1, TIM_Channel_1, 1000.0);         // Output on PA8
    PWM_QuickInit_Complementary(TIM1, TIM_Channel_1);   // Output on PB13
    
    PWM_SetDutyCycle(TIM1, TIM_Channel_1, 0.75);
    PWM_Start(TIM1);
}

/* Private functions ---------------------------------------------------------*/
