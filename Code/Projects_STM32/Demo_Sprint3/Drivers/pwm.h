/**
 * @file motor.h
 * @author Curtis team
 * @brief Service library that allows to manipulate motors
 */


#ifndef PWM_H
#define PWM_H

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
void pwm_init(TIM_TypeDef *timer, uint16_t channel, float frequency_PWM_Hz);

//active le timer associ� � la PWM
void pwm_enable(TIM_TypeDef *timer);

//d�sactive le timer associ� � la PWM
void pwm_disable(TIM_TypeDef *timer);

void pwm_set_duty_cycle(TIM_TypeDef *Timer, uint16_t channel, float duty_cycle);

//configure la bonne sortie au timer et � la voie choisis
void pwm_port_init(TIM_TypeDef *Timer, uint16_t channel);

//active la sortie complementaire � un PWM initialis�
void active_complementary_output(TIM_TypeDef *timer, uint16_t channel, int remap);

////active l'option one shoot du PWM
//void output_compare_init(TIM_TypeDef *Timer, int channel, float period_us);

////active le timer associ� au one-pulse
//void output_compare_start(TIM_TypeDef *Timer);

//void capture_input_init(TIM_TypeDef *Timer, int channel);
//void capture_start(TIM_TypeDef *Timer, int channel);
//uint16_t capture_get_high_state_periode(void);

#endif // PWM_H
