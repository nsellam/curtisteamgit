#include "pwm.h"

#include <stm32f10x.h>

#include <system_stm32f10x.h>
#include <timer.h>
#include <gpio2.h>

//------- Private functions -----------


//------- Public functions ------------

float PWM_Init(TIM_TypeDef *Timer, int Channel, float Frequence_PWM_Hz) {
   float duree_pwm_usec = US_PER_S/Frequence_PWM_Hz;  // duree_pwm en micro secondes
   float freq_pwm_vraie = 0.0;

   duree_pwm_usec = Timer_1234_Init(Timer, duree_pwm_usec);  //donne la duree v�ritable du pwm en micro sec

   switch(Channel) {
      case 1 :
         //output compare: PWM Mode 1
         Timer->CCMR1 &= ~TIM_CCMR1_OC1M; //met � 0 tous les bits
         Timer->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont � 1

         //channel 1 en mode output compare
         Timer->CCMR1 &= ~TIM_CCMR1_CC1S;

         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC1E;    
         break;

      case 2 :
         //output compare: PWM Mode 1
         Timer->CCMR1 &= ~TIM_CCMR1_OC2M; //met � 0 tous les bits
         Timer->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont � 1

         //channel 2 en mode output compare
         Timer->CCMR1 &= ~TIM_CCMR1_CC2S;

         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC2E;
         break;

      case 3 :
         //output compare: PWM Mode 1
         Timer->CCMR2 &= ~TIM_CCMR2_OC3M; //met � 0 tous les bits
         Timer->CCMR2 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont � 1

         //channel 3 en mode output compare
         Timer->CCMR2 &= ~TIM_CCMR2_CC3S;

         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC3E;
         break;

      case 4 :
         //output compare: PWM Mode 1
         Timer->CCMR2 &= ~TIM_CCMR2_OC4M; //met � 0 tous les bits
         Timer->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);  // mode 1 pour upcounting (mettre 110 dans OCx), ici met le bit 1 et 2 sont � 1

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


   return freq_pwm_vraie;    // retourne freq r�elle du pwm
}

void PWM_Set_Duty_Cycle(TIM_TypeDef *Timer, int Channel, float duty_cycle) {
   uint16_t pulse_length_nbre = 0; // nbre entier non sign� de 16 bits
   uint16_t resolution;
   resolution = Timer->ARR;

   //Timer->CCER=Timer->CCER|(1<<((Channel-1)*4)); //enable le capture/compare de la voie s�lectionn�e

   pulse_length_nbre = (int)((float)resolution*duty_cycle);  // duty entre 0.0 et 1.0
   
   switch(Channel) {
      case 1 :
         Timer->CCR1 = pulse_length_nbre; //stockage de l'�tat haut
         break;
      case 2 :
         Timer->CCR2 = pulse_length_nbre;
         break;
      case 3 :
         Timer->CCR3 = pulse_length_nbre;
         break;
      case 4 :
         Timer->CCR4 = pulse_length_nbre;
         break;

      default:
         break;
   }
   Timer->EGR |= TIM_EGR_UG;
}

void PWM_Enable(TIM_TypeDef *Timer)
{
   Timer_1234_Enable(Timer); //enable le timer

}


void PWM_Disable(TIM_TypeDef *Timer)
{
   Timer_1234_Disable(Timer);  //disable le timer
}

void PWM_Port_Init(TIM_TypeDef *Timer, int Channel)
{

   if (Timer == TIM1)
   {
      Port_IO_Clock_Enable(GPIOA);
      switch (Channel)
      {
         case 1 :
            Port_IO_Init_Output_AltFunct(GPIOA, 8);
            break;
         case 2 :
            Port_IO_Init_Output_AltFunct(GPIOA, 9);
            break;
         case 3 :
            Port_IO_Init_Output_AltFunct(GPIOA, 10);
            break;
         case 4 :
            Port_IO_Init_Output_AltFunct(GPIOA, 11);
            break;

         default:
            break;
      }
   }

   else if (Timer == TIM2)
   {
      Port_IO_Clock_Enable(GPIOA);
      switch (Channel)
      {
         case 1 :
            Port_IO_Init_Output_AltFunct(GPIOA, 0);
            break;
         case 2 :
            Port_IO_Init_Output_AltFunct(GPIOA, 1);
            break;
         case 3 :
            Port_IO_Init_Output_AltFunct(GPIOA, 2);
            break;
         case 4 :
            Port_IO_Init_Output_AltFunct(GPIOA, 3);
            break;

         default:
            break;
      }
   }


   else if (Timer == TIM3)
   {
      switch (Channel)
      {
         case 1 :
            Port_IO_Clock_Enable(GPIOA);
            Port_IO_Init_Output_AltFunct(GPIOA, 6);
            break;
         case 2 :
            Port_IO_Clock_Enable(GPIOA);
            Port_IO_Init_Output_AltFunct(GPIOA, 7);
            break;
         case 3 :
            Port_IO_Clock_Enable(GPIOB);
            Port_IO_Init_Output_AltFunct(GPIOB, 0);
            break;
         case 4 :
            Port_IO_Clock_Enable(GPIOB);
            Port_IO_Init_Output_AltFunct(GPIOB, 1);
            break;

         default:
            break;
      }
   }


   else if (Timer == TIM4)
   {
      Port_IO_Clock_Enable(GPIOB);
      switch (Channel)
      {
         case 1 :
            Port_IO_Init_Output_AltFunct(GPIOB, 6);
            break;
         case 2 :
            Port_IO_Init_Output_AltFunct(GPIOB, 7);
            break;
         case 3 :
            Port_IO_Init_Output_AltFunct(GPIOB, 8);
            break;
         case 4 :
            Port_IO_Init_Output_AltFunct(GPIOB, 9);
            break;

         default:
            break;
      }
   }

}




//active la sortie complementaire � un PWM initialis�
void Active_Complementary_Output(TIM_TypeDef *Timer, int Channel){
   switch(Channel) {
      case 1 :
         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC1NE;    
         break;

      case 2 :
         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC2NE;
         break;

      case 3 :
         //output compare channel enable
         Timer->CCER |= TIM_CCER_CC3NE;
         break;

      default:
         break;
   }

   if (Timer == TIM1){
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
      Port_IO_Clock_Enable(GPIOA);
      Port_IO_Clock_Enable(GPIOB);
      GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
      switch (Channel)
      {
         case 1 :
            Port_IO_Init_Output_AltFunct(GPIOA, 7);
            break;
         case 2 :
            Port_IO_Init_Output_AltFunct(GPIOB, 14);
            break;
         case 3 :
            Port_IO_Init_Output_AltFunct(GPIOB, 15);
            break;

         default:
            break;
      }
   }

}




void output_compare_init(TIM_TypeDef *Timer, int Channel, float period_us){
   
   Timer_1234_Init(Timer, 2*period_us);
   Timer->CCR1 = (uint16_t) ((Timer->ARR)/2);      
   
   switch(Channel) {
      case 1 :
         // active interrupt request
         Timer->DIER |= TIM_DIER_CC1IE;
      
         // toogle OCx output pin when CNT matches CCRx
         Timer->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0);
         
         // disable preload
         Timer->CCMR1 &= ~TIM_CCMR1_OC1PE;
      
         // select active high polarity
         Timer->CCER &= ~TIM_CCER_CC1P;
         
         // enable the output
         Timer->CCER |= TIM_CCER_CC1E;      
      
         break;
      case 2 :
             
         break;
      
      case 3 :

         
         break;
      case 4 :

             
         break;
      
      default:
         break;
      }
}

   
void output_compare_start(TIM_TypeDef *Timer){
   Timer->CR1 |= TIM_CCER_CC1E;
}


void capture_input_init(TIM_TypeDef *Timer, int Channel){
   switch (Channel){
      case 1:
         // select active input on TI1
         Timer->CCMR1 |= TIM_CCMR1_CC1S_0;
         Timer->CCMR1 &= ~TIM_CCMR1_CC1S_1;
         
         // frequency filter to 
         Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
      
         // select rising edge to active transition
         Timer->CCER &= ~TIM_CCER_CC1P;
      
         // disable prescale
         //Timer->CCMR1 &= ~TIM_CCMR1_IC1PS;
      
         // enable capture interrupt
         Timer->DIER |= TIM_DIER_CC1IE;
            
      
      break;
      case 2:
         
      break;
      case 3:
         
      break;
      case 4:
         
      break;
      
      default:
      break;
      
   }
}

/*void capture_GPIO_init(TIM_TypeDef *Timer, int Channel){
   if(Timer == TIM1){
      GPIO_DeInit(GPIOA);
      switch(Channel){
         case 1:
            f
         break;
         
      }
   
   }
   
}*/
/*void capture_start(TIM_TypeDef *Timer, int Channel){
   // enable capture interrupt
   Timer->DIER |= TIM_DIER_CC1IE;
}*/

/*uint16_t capture_get_high_state_periode(TIM_TypeDef *Timer, int Channel){
      
}*/