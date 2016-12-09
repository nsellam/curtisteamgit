/**
 * @file motor.h
 * @author Curtis team
 * @brief Service library that allows to manipulate motors
 */


#ifndef _PWM_H_
#define _PWM_H_

#include <stm32f10x.h>


/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn motors_init
* @brief Initializes motors drivers 
* @param void
* @return void
*/
float PWM_Init(TIM_TypeDef *Timer, int Channel, float Frequence_PWM_Hz);

void PWM_Set_Duty_Cycle(TIM_TypeDef *Timer, int Channel, float duty_cycle);

//active le timer associé à la PWM
void PWM_Enable(TIM_TypeDef *Timer);

//désactive le timer associé à la PWM
void PWM_Disable(TIM_TypeDef *Timer);

//configure la bonne sortie au timer et à la voie choisis
void PWM_Port_Init(TIM_TypeDef *Timer, int Channel);

//active la sortie complementaire à un PWM initialisé
void Active_Complementary_Output(TIM_TypeDef *Timer, int Channel);

//active l'option one shoot du PWM
void output_compare_init(TIM_TypeDef *Timer, int Channel, float period_us);

//active le timer associé au one-pulse
void output_compare_start(TIM_TypeDef *Timer);

void capture_input_init(TIM_TypeDef *Timer, int Channel);
void capture_start(TIM_TypeDef *Timer, int Channel);
uint16_t capture_get_high_state_periode(void);

#endif // _PWM_H_
