//#include "pwm.h"

//#include <stm32f10x.h>

//#include "timer.h"
//#include "gpio.h"

//

////------- Private functions -----------


////------- Public functions ------------

//float PWM_Init(TIM_TypeDef *Timer, int channel, float frequency_PWM_Hz) {
//   float duree_pwm_usec = US_PER_S/frequency_PWM_Hz;  // duree_pwm en micro secondes
//   float freq_pwm_vraie = 0.0;

//   duree_pwm_usec = Timer_1234_Init(Timer, duree_pwm_usec);  //donne la duree véritable du pwm en micro sec

//   switch(channel) {
//      case 1 :
//         //output compare: PWM Mode 1
//         Timer->CCMR1 &= ~TIM_CCMR1_OC1M; //met à 0 tous les bits
//         Timer->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

//         //channel 1 en mode output compare
//         Timer->CCMR1 &= ~TIM_CCMR1_CC1S;

//         //output compare channel enable
//         Timer->CCER |= TIM_CCER_CC1E;    
//         break;

//      case 2 :
//         //output compare: PWM Mode 1
//         Timer->CCMR1 &= ~TIM_CCMR1_OC2M; //met à 0 tous les bits
//         Timer->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

//         //channel 2 en mode output compare
//         Timer->CCMR1 &= ~TIM_CCMR1_CC2S;

//         //output compare channel enable
//         Timer->CCER |= TIM_CCER_CC2E;
//         break;

//      case 3 :
//         //output compare: PWM Mode 1
//         Timer->CCMR2 &= ~TIM_CCMR2_OC3M; //met à 0 tous les bits
//         Timer->CCMR2 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

//         //channel 3 en mode output compare
//         Timer->CCMR2 &= ~TIM_CCMR2_CC3S;

//         //output compare channel enable
//         Timer->CCER |= TIM_CCER_CC3E;
//         break;

//      case 4 :
//         //output compare: PWM Mode 1
//         Timer->CCMR2 &= ~TIM_CCMR2_OC4M; //met à 0 tous les bits
//         Timer->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont à 1

//         //channel 4 en mode output compare
//         Timer->CCMR2 &= ~TIM_CCMR2_CC4S;

//         //output compare channel enable
//         Timer->CCER |= TIM_CCER_CC4E;
//         break;

//      default:
//         break;
//   }

//   if(Timer == TIM1)
//      Timer->BDTR |= TIM_BDTR_MOE;

//   // conversion temps /freq
//   freq_pwm_vraie = US_PER_S/duree_pwm_usec;  // freq en Hz


//   return freq_pwm_vraie;    // retourne freq réelle du pwm
//}

//void PWM_Set_Duty_Cycle(TIM_TypeDef *Timer, int channel, float duty_cycle) {
//   uint16_t pulse_length_nbre = 0; // nbre entier non signé de 16 bits
//   uint16_t resolution;
//   resolution = Timer->ARR;

//   //Timer->CCER=Timer->CCER|(1<<((channel-1)*4)); //enable le capture/compare de la voie sélectionnée

//   pulse_length_nbre = (int)((float)resolution*duty_cycle);  // duty entre 0.0 et 1.0
//   
//   switch(channel) {
//      case 1 :
//         Timer->CCR1 = pulse_length_nbre; //stockage de l'état haut
//         break;
//      case 2 :
//         Timer->CCR2 = pulse_length_nbre;
//         break;
//      case 3 :
//         Timer->CCR3 = pulse_length_nbre;
//         break;
//      case 4 :
//         Timer->CCR4 = pulse_length_nbre;
//         break;

//      default:
//         break;
//   }
//   Timer->EGR |= TIM_EGR_UG;
//}








////active la sortie complementaire à un PWM initialisé
//void Active_Complementary_Output(TIM_TypeDef *Timer, int channel, int remap){
//   if (Timer == TIM1) {
//      switch(channel) {
//         case 1 :
//            //output compare channel enable
//            Timer->CCER |= TIM_CCER_CC1NE;    
//            break;

//         case 2 :
//            //output compare channel enable
//            Timer->CCER |= TIM_CCER_CC2NE;
//            break;

//         case 3 :
//            //output compare channel enable
//            Timer->CCER |= TIM_CCER_CC3NE;
//            break;

//         default:
//            break;
//      }

//      if(remap) {
//         RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//         GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
//         switch (channel) {
//            case 1: GPIO_QuickInit(GPIOA, GPIO_Pin_7, PWM_GPIO_MODE); break;
//            case 2: GPIO_QuickInit(GPIOB, GPIO_Pin_0, PWM_GPIO_MODE); break;
//            case 3: GPIO_QuickInit(GPIOB, GPIO_Pin_1, PWM_GPIO_MODE); break;
//            default: break;
//         }
//      } else {
//         switch (channel) {
//            case 1: GPIO_QuickInit(GPIOB, GPIO_Pin_13, PWM_GPIO_MODE); break;
//            case 2: GPIO_QuickInit(GPIOB, GPIO_Pin_14, PWM_GPIO_MODE); break;
//            case 3: GPIO_QuickInit(GPIOB, GPIO_Pin_15, PWM_GPIO_MODE); break;
//            default: break;
//         }
//      }
//   }

//}




//void output_compare_init(TIM_TypeDef *Timer, int channel, float period_us){
//   
//   Timer_1234_Init(Timer, 2*period_us);
//   Timer->CCR1 = (uint16_t) ((Timer->ARR)/2);      
//   
//   switch(channel) {
//      case 1 :
//         // active interrupt request
//         Timer->DIER |= TIM_DIER_CC1IE;
//      
//         // toogle OCx output pin when CNT matches CCRx
//         Timer->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0);
//         
//         // disable preload
//         Timer->CCMR1 &= ~TIM_CCMR1_OC1PE;
//      
//         // select active high polarity
//         Timer->CCER &= ~TIM_CCER_CC1P;
//         
//         // enable the output
//         Timer->CCER |= TIM_CCER_CC1E;      
//      
//         break;
//      case 2 :
//             
//         break;
//      
//      case 3 :

//         
//         break;
//      case 4 :

//             
//         break;
//      
//      default:
//         break;
//      }
//}

//   
//void output_compare_start(TIM_TypeDef *Timer){
//   Timer->CR1 |= TIM_CCER_CC1E;
//}


//void capture_input_init(TIM_TypeDef *Timer, int channel){
//   switch (channel){
//      case 1:
//         // select active input on TI1
//         Timer->CCMR1 |= TIM_CCMR1_CC1S_0;
//         Timer->CCMR1 &= ~TIM_CCMR1_CC1S_1;
//         
//         // frequency filter to 
//         Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
//      
//         // select rising edge to active transition
//         Timer->CCER &= ~TIM_CCER_CC1P;
//      
//         // disable prescale
//         //Timer->CCMR1 &= ~TIM_CCMR1_IC1PS;
//      
//         // enable capture interrupt
//         Timer->DIER |= TIM_DIER_CC1IE;
//            
//      
//      break;
//      case 2:
//         
//      break;
//      case 3:
//         
//      break;
//      case 4:
//         
//      break;
//      
//      default:
//      break;
//      
//   }
//}

///*void capture_GPIO_init(TIM_TypeDef *Timer, int channel){
//   if(Timer == TIM1){
//      GPIO_DeInit(GPIOA);
//      switch(channel){
//         case 1:
//            f
//         break;
//         
//      }
//   
//   }
//   
//}*/
///*void capture_start(TIM_TypeDef *Timer, int channel){
//   // enable capture interrupt
//   Timer->DIER |= TIM_DIER_CC1IE;
//}*/

///*uint16_t capture_get_high_state_periode(TIM_TypeDef *Timer, int channel){
//      
//}*/



 
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


void pwm_set_duty_cycle(TIM_TypeDef *timer, int channel, float duty_cycle) {
   uint16_t pulse_length_nbre = 0; // nbre entier non signé de 16 bits
   uint16_t resolution;
   resolution = timer->ARR;

   pulse_length_nbre = (int)((float)resolution*duty_cycle);  // duty entre 0.0 et 1.0
        
   switch(channel) {
      case 1 :
         timer->CCR1 = pulse_length_nbre; //stockage de l'état haut
         break;
      case 2 :
         timer->CCR2 = pulse_length_nbre;
         break;
      case 3 :
         timer->CCR3 = pulse_length_nbre;
         break;
      case 4 :
         timer->CCR4 = pulse_length_nbre;
         break;

      default:
         break;
   }
   timer->EGR |= TIM_EGR_UG;
}


void pwm_port_init(TIM_TypeDef *timer, int channel) {
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
   
   TIM_CCxNCmd	(timer, channel, TIM_CCxN_Enable);
   
//   if (Timer == TIM1) {
//      switch(channel) {
//         case 1 :
//            //output compare channel enable
//            TIM_CCxNCmd	(Timer, channel,uint16_t TIM_CCxN_Enable);	   
//            break;

//         case 2 :
//            //output compare channel enable
//            Timer->CCER |= TIM_CCER_CC2NE;
//            break;

//         case 3 :
//            //output compare channel enable
//            Timer->CCER |= TIM_CCER_CC3NE;
//            break;

//         default:
//            break;
//      }

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
   //}

}

