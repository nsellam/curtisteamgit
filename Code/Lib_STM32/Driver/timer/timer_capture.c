#include "timer_capture.h"

#include <stdint.h>
#include <stm32f10x.h>
#include <timer.h>
#include <gpio.h>


void compare_output_init(TIM_TypeDef *Timer, uint8_t Channel, float Frequence_PWM_Hz){
   
   float duree_pwm_usec = US_PER_S/Frequence_PWM_Hz;  // duree_pwm en micro secondes
   float freq_pwm_vraie = 0.0;

   duree_pwm_usec = Timer_1234_Init(Timer, duree_pwm_usec);  //donne la duree véritable du pwm en micro sec

   switch(Channel) {
      case 1 :
         //output compare: PWM Mode 1
         Timer->CCMR1 &= ~TIM_CCMR1_OC1M; //met à 0 tous les bits
         Timer->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

         //channel 1 en mode output compare
         Timer->CCMR1 &= ~TIM_CCMR1_CC1S;

         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC1E;    
         break;

      case 2 :
         //output compare: PWM Mode 1
         Timer->CCMR1 &= ~TIM_CCMR1_OC2M; //met à 0 tous les bits
         Timer->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

         //channel 2 en mode output compare
         Timer->CCMR1 &= ~TIM_CCMR1_CC2S;

         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC2E;
         break;

      case 3 :
         //output compare: PWM Mode 1
         Timer->CCMR2 &= ~TIM_CCMR2_OC3M; //met à 0 tous les bits
         Timer->CCMR2 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

         //channel 3 en mode output compare
         Timer->CCMR2 &= ~TIM_CCMR2_CC3S;

         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC3E;
         break;

      case 4 :
         //output compare: PWM Mode 1
         Timer->CCMR2 &= ~TIM_CCMR2_OC4M; //met à 0 tous les bits
         Timer->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

         //channel 4 en mode output compare
         Timer->CCMR2 &= ~TIM_CCMR2_CC4S;

         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC4E;
         break;

      default:
         break;
   }

   if(Timer == TIM1)
      Timer->BDTR |= TIM_BDTR_MOE;

   // conversion temps /freq
   freq_pwm_vraie = US_PER_S/duree_pwm_usec;  // freq en Hz


   return freq_pwm_vraie;    // retourne freq réelle du pwm
}

void compare_output_start(TIM_TypeDef *Timer, uint8_t Channel){
   
	if (Channel == 1)       Timer->CR1 |= TIM_CR1_CEN;
   else if (Channel == 2)  Timer->CCER |= TIM_CCER_CC2E;
   else if (Channel == 3)  Timer->CCER |= TIM_CCER_CC3E;
   else if (Channel == 4)  Timer->CCER |= TIM_CCER_CC4E;
}



/**
  * @brief  Initializes a Timer in mode Input Capture at Channel with:
	*		No filter, sampling at fDTS, no presclaer, polarity at falling edge, capture interrupt enable
  * @param  Timer  : Can be TIM1 - TIM5
	* @param  Channel: The channel which will receive the input signal, can receive values from 1 to 4
	*		Referenced to the timer input mapping
  * @retval None
  */
void TIM_Capt_Init(TIM_TypeDef *Timer, uint8_t Channel) {

	if (Channel == 1) {

		/* Disable Capture mode */
		Timer->CCER &= ~TIM_CCER_CC1E;
		/* No filter, sampling is done at fDTS */
		Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
		/* No Prescaler */
		Timer->CCMR1 &= ~TIM_CCMR1_IC1PSC;
		/* Input selection TI1 */
		Timer->CCMR1 &= ~TIM_CCMR1_CC1S;
		Timer->CCMR1 |= TIM_CCMR1_CC1S_0;
		/* Enable capture interrupt request */
		Timer->DIER |= TIM_DIER_CC1IE;
		/* Set polarity at falling edge */
		Timer->CCER |= TIM_CCER_CC1P;
		/* Enable Capture mode */
		Timer->CCER |= TIM_CCER_CC1E;

	} else if (Channel == 2) {

		Timer->CCER &= ~TIM_CCER_CC2E;
		Timer->CCMR1 &= ~TIM_CCMR1_IC2F;
		Timer->CCMR1 &= ~TIM_CCMR1_IC2PSC;
		Timer->CCMR1 &= ~TIM_CCMR1_CC2S;
		Timer->CCMR1 |= TIM_CCMR1_CC2S_0;
		Timer->DIER |= TIM_DIER_CC2IE;
		Timer->CCER |= TIM_CCER_CC2P;
		Timer->CCER |= TIM_CCER_CC2E;

	} else if (Channel == 3) {

		Timer->CCER &= ~TIM_CCER_CC3E;
		Timer->CCMR2 &= ~TIM_CCMR2_IC3F;
		Timer->CCMR2 &= ~TIM_CCMR2_IC3PSC;
		Timer->CCMR2 &= ~TIM_CCMR2_CC3S;
		Timer->CCMR2 |= TIM_CCMR2_CC3S_0;
		Timer->DIER |= TIM_DIER_CC3IE;
		Timer->CCER |= TIM_CCER_CC3P;
		Timer->CCER |= TIM_CCER_CC3E;

	} else if (Channel == 4) {

		Timer->CCER &= ~TIM_CCER_CC4E;
		Timer->CCMR2 &= ~TIM_CCMR2_IC4F;
		Timer->CCMR2 &= ~TIM_CCMR2_IC4PSC;
		Timer->CCMR2 &= ~TIM_CCMR2_CC4S;
		Timer->CCMR2 |= TIM_CCMR2_CC4S_0;
		Timer->DIER |= TIM_DIER_CC4IE;
		Timer->CCER |= TIM_CCER_CC4P;
		Timer->CCER |= TIM_CCER_CC4E;

	}

}


/**
  * @brief  Get the counter value when capture event happens
  * @param  Timer  : Can be TIM1 - TIM5
	* @param  Channel: The channel which will receive the input signal, can receive values from 1 to 4
	*		Referenced to the timer input mapping
  * @retval Capture Compare Register value
  */
uint16_t GetCaptureVal(TIM_TypeDef *Timer, uint8_t Channel) {

	if (Channel == 1)
		return Timer->CCR1;
	else if (Channel == 2)
		return Timer->CCR2;
	else if (Channel == 3)
		return Timer->CCR3;
	else if (Channel == 4)
		return Timer->CCR4;
	else return 0;

}

void PWM_In_Mode_TI1(TIM_TypeDef *Timer) {

		/* TI1FP1 is the trigger input */
		Timer->SMCR &= ~TIM_SMCR_TS;
		Timer->SMCR |= TIM_SMCR_TS_0 | TIM_SMCR_TS_2;
		/* Reset mode on trigger */
		Timer->SMCR &= ~TIM_SMCR_SMS;
		Timer->SMCR |= TIM_SMCR_SMS_2;

		/* For IC1 signal */
		/* Disable Capture mode CC1 */
		Timer->CCER &= ~TIM_CCER_CC1E;

		/* Disable Capture mode CC2 */
		Timer->CCER &= ~TIM_CCER_CC2E;

		/* No filter, sampling is done at fDTS */
		Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
		/* No Prescaler */
		Timer->CCMR1 &= ~TIM_CCMR1_IC1PSC;
		/* Input selection IC1 mapped on TI1 */
		Timer->CCMR1 &= ~TIM_CCMR1_CC1S;
		Timer->CCMR1 |= TIM_CCMR1_CC1S_0;
		/* Enable capture interrupt request */
		Timer->DIER |= TIM_DIER_CC1IE;
		/* Set polarity at rising edge */
		Timer->CCER &= ~TIM_CCER_CC1P;
		/* Enable Capture mode */
		Timer->CCER |= TIM_CCER_CC1E;

		/* For IC2 signal */
		/* No filter, sampling is done at fDTS */
		Timer->CCMR1 &= ~TIM_CCMR1_IC2F;
		/* No Prescaler */
		Timer->CCMR1 &= ~TIM_CCMR1_IC2PSC;
		/* Input selection IC2 mapped on TI1 */
		Timer->CCMR1 &= ~TIM_CCMR1_CC2S;
		Timer->CCMR1 |= TIM_CCMR1_CC2S_1;
		/* Enable capture interrupt request */
		Timer->DIER |= TIM_DIER_CC2IE;
		/* Set polarity at falling edge */
		Timer->CCER |= TIM_CCER_CC2P;
		/* Enable Capture mode */
		Timer->CCER |= TIM_CCER_CC2E;

}

void PWM_In_Mode_TI2(TIM_TypeDef *Timer) {

		/* TI2FP2 is the trigger input */
		Timer->SMCR &= ~TIM_SMCR_TS;
		Timer->SMCR |= TIM_SMCR_TS_1 | TIM_SMCR_TS_2;
		/* Reset mode on trigger */
		Timer->SMCR &= ~TIM_SMCR_SMS;
		Timer->SMCR |= TIM_SMCR_SMS_2;

		/* Disable Capture mode CC1 */
		Timer->CCER &= ~TIM_CCER_CC1E;

		/* Disable Capture mode CC2 */
		Timer->CCER &= ~TIM_CCER_CC2E;

		/* For IC1 signal */
		/* No filter, sampling is done at fDTS */
		Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
		/* No Prescaler */
		Timer->CCMR1 &= ~TIM_CCMR1_IC1PSC;
		/* Input selection IC1 mapped on TI2 */
		Timer->CCMR1 &= ~TIM_CCMR1_CC1S;
		Timer->CCMR1 |= TIM_CCMR1_CC1S_1;
		/* Enable capture interrupt request */
		Timer->DIER |= TIM_DIER_CC1IE;
		/* Set polarity at falling edge */
		Timer->CCER |= TIM_CCER_CC1P;
		/* Enable Capture mode */
		Timer->CCER |= TIM_CCER_CC1E;

		/* For IC2 signal */
		/* No filter, sampling is done at fDTS */
		Timer->CCMR1 &= ~TIM_CCMR1_IC2F;
		/* No Prescaler */
		Timer->CCMR1 &= ~TIM_CCMR1_IC2PSC;
		/* Input selection IC2 mapped on TI2 */
		Timer->CCMR1 &= ~TIM_CCMR1_CC2S;
		Timer->CCMR1 |= TIM_CCMR1_CC2S_0;
		/* Enable capture interrupt request */
		Timer->DIER |= TIM_DIER_CC2IE;
		/* Set polarity at rising edge */
		Timer->CCER &= ~TIM_CCER_CC2P;
		/* Enable Capture mode */
		Timer->CCER |= TIM_CCER_CC2E;

}

void PWM_In_Mode_Port_Clock_Init(TIM_TypeDef *Timer) {
   if (Timer == TIM1)
   {
      Port_IO_Clock_Enable(GPIOA);
   }

   else if (Timer == TIM2)
   {
      Port_IO_Clock_Enable(GPIOA);
   }


   else if (Timer == TIM3)
   {
      Port_IO_Clock_Enable(GPIOA);
      Port_IO_Clock_Enable(GPIOB);
   }


   else if (Timer == TIM4)
   {
      Port_IO_Clock_Enable(GPIOB);
   }
}
