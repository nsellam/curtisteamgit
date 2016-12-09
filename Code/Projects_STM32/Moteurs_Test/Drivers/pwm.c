#include "pwm.h"

#include "stm32f10x_tim.h"
#include "timer.h"
#include "gpio.h"
#include "misc.h"
 
#define PWM_GPIO_MODE GPIO_Mode_AF_PP


void pwm_init(TIM_TypeDef *timer, uint16_t channel, float frequency_PWM_Hz){  
  float duree_pwm_usec = US_PER_S/frequency_PWM_Hz;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
   
  timer_init(timer, duree_pwm_usec);
  
  /* always initialise local variables before use */
  TIM_OCStructInit (&TIM_OCInitStructure);
  /* Common settings for all channels */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = 0;
  
  if(channel == 1)       TIM_OC1Init(timer, &TIM_OCInitStructure); 
  else if(channel == 2)  TIM_OC2Init(timer, &TIM_OCInitStructure);
  else if(channel == 3)  TIM_OC3Init(timer, &TIM_OCInitStructure);
  else if(channel == 4)  TIM_OC4Init(timer, &TIM_OCInitStructure);
   
  if(timer == TIM1)
      timer->BDTR |= TIM_BDTR_MOE; 
}


void pwm_enable(TIM_TypeDef *timer)
{
   timer_start(timer); 
}


void pwm_Disable(TIM_TypeDef *timer)
{
   timer_disable(timer);  
}


void pwm_set_duty_cycle(TIM_TypeDef *timer, uint16_t channel, float duty_cycle) {
   volatile uint16_t pulse_length = 0; // nbre entier non signé de 16 bits
   uint16_t resolution;
   resolution = timer->ARR;

   pulse_length = (uint16_t)((float)resolution*duty_cycle);  // duty entre 0.0 et 1.0
        
   switch(channel) {
      case 1 :
         TIM_SetCompare1(timer,pulse_length);	
         break;
      case 2 :
         TIM_SetCompare2(timer,pulse_length);	
         break;
      case 3 :
         TIM_SetCompare3(timer,pulse_length);	
         break;
      case 4 :
         TIM_SetCompare4(timer,pulse_length);	
         break;

      default:
         break;
   }
   timer->EGR |= TIM_EGR_UG;
}


void pwm_port_init(TIM_TypeDef *timer, uint16_t channel) {
   if (timer == TIM1) {
      switch (channel) {
         case 1: GPIO_QuickInit(GPIOA, GPIO_Pin_8 , PWM_GPIO_MODE); break;
         case 2: GPIO_QuickInit(GPIOA, GPIO_Pin_9 , PWM_GPIO_MODE); break;
         case 3: GPIO_QuickInit(GPIOA, GPIO_Pin_10, PWM_GPIO_MODE); break;
         case 4: GPIO_QuickInit(GPIOA, GPIO_Pin_11, PWM_GPIO_MODE); break;
         default: break;
      }
   }
   else if (timer == TIM2) {
      switch (channel) {
         case 1: GPIO_QuickInit(GPIOA, GPIO_Pin_0, PWM_GPIO_MODE); break;
         case 2: GPIO_QuickInit(GPIOA, GPIO_Pin_1, PWM_GPIO_MODE); break;
         case 3: GPIO_QuickInit(GPIOA, GPIO_Pin_2, PWM_GPIO_MODE); break;
         case 4: GPIO_QuickInit(GPIOA, GPIO_Pin_3, PWM_GPIO_MODE); break;
         default: break;
      }
   }
   else if (timer == TIM3) {
      switch (channel) {
         case 1: GPIO_QuickInit(GPIOA, GPIO_Pin_6, PWM_GPIO_MODE); break;
         case 2: GPIO_QuickInit(GPIOA, GPIO_Pin_7, PWM_GPIO_MODE); break;
         case 3: GPIO_QuickInit(GPIOB, GPIO_Pin_0, PWM_GPIO_MODE); break;
         case 4: GPIO_QuickInit(GPIOB, GPIO_Pin_1, PWM_GPIO_MODE); break;
         default: break;
      }
   }
   else if (timer == TIM4) {
      switch (channel) {
         case 1: GPIO_QuickInit(GPIOB, GPIO_Pin_6, PWM_GPIO_MODE); break;
         case 2: GPIO_QuickInit(GPIOB, GPIO_Pin_7, PWM_GPIO_MODE); break;
         case 3: GPIO_QuickInit(GPIOB, GPIO_Pin_8, PWM_GPIO_MODE); break;
         case 4: GPIO_QuickInit(GPIOB, GPIO_Pin_9, PWM_GPIO_MODE); break;
         default: break;
      }
   }

} 

 ////active la sortie complementaire à un PWM initialisé
void active_complementary_output(TIM_TypeDef *timer, uint16_t channel, int remap){
   
      if (timer == TIM1) {
      switch(channel) {
         case 1 :
            //output compare channel enable
            TIM_CCxNCmd	(timer, channel,uint16_t TIM_CCxN_Enable);
            
            //timer->CCER |= TIM_CCER_CC1NE;
            break;

         case 2 :
            //output compare channel enable
            timer->CCER |= TIM_CCER_CC2NE;
            break;

         case 3 :
            //output compare channel enable
            timer->CCER |= TIM_CCER_CC3NE;
            break;

         default:
            break;
      }
      }
   if(remap) {
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
      switch (channel) {
         case 1: GPIO_QuickInit(GPIOA, GPIO_Pin_7, PWM_GPIO_MODE); break;
         case 2: GPIO_QuickInit(GPIOB, GPIO_Pin_0, PWM_GPIO_MODE); break;
         case 3: GPIO_QuickInit(GPIOB, GPIO_Pin_1, PWM_GPIO_MODE); break;
         default: break;
      }
    } else {
       switch (channel) {
         case 1: GPIO_QuickInit(GPIOB, GPIO_Pin_13, PWM_GPIO_MODE); break;
         case 2: GPIO_QuickInit(GPIOB, GPIO_Pin_14, PWM_GPIO_MODE); break;
         case 3: GPIO_QuickInit(GPIOB, GPIO_Pin_15, PWM_GPIO_MODE); break;
         default: break;
         }
    }

}

