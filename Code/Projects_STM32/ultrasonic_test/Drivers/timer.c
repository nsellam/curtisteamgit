#include "timer.h"

/********************************/
/*       LIBRARIES              */
/********************************/
#include "timer.h"
#include "gpio.h"

#include <stdint.h>
#include <stm32f10x.h>
#include <stm32f10x_tim.h>






/********************************/
/*         CONSTANTS            */
/********************************/

/* unfortunate globals */
#define PWM_frequency 100
#define PWM_steps 100

/**
* @def PSC_VALUE_MIN
* @brief Min Value of Prescaler register in STM32
*/
#define PSC_VALUE_MIN ((uint16_t)0)     // CK_CNT = 72MHz

/**
* @def PSC_VALUE_MAX
* @brief Max Value of Prescaler register in STM32
*/
#define PSC_VALUE_MAX ((uint16_t)65535) // CK_CNT ~ 1.1kHz

/**
* @def ARR_VALUE_MIN
* @brief Min Value of Autoreload register in STM32
*/
#define ARR_VALUE_MIN ((uint16_t)0)

/**
* @def ARR_VALUE_MAX
* @brief Max Value of Autoreload register in STM32
*/
#define ARR_VALUE_MAX ((uint16_t)65535)

/**
* @def SYSTEM_CORE_CLOCK
* @brief Clock value in STM32
*/
#define SYSTEM_CORE_CLOCK 72.0e6

#define PSC_CEILING_LIMIT 1.0e-6



/********************************/
/*       FUNCTIONS              */
/********************************/

//------- Private prototypes ----------

// IRQ Handlers
void (*TIM1_IT_Function)(void);
void (*TIM2_IT_Function)(void);
void (*TIM3_IT_Function)(void);
void (*TIM4_IT_Function)(void);


//------- Handlers functions -----------

void TIM1_UP_IRQHandler(void) {
   if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET){
         TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
         TIM1_IT_Function();
   } else if(TIM_GetITStatus(TIM1,TIM_IT_CC1) != RESET){
         TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
         TIM1_IT_Function();
   } else if(TIM_GetITStatus(TIM1,TIM_IT_CC2) != RESET){
         TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
         TIM1_IT_Function();
   } else if(TIM_GetITStatus(TIM1,TIM_IT_CC3) != RESET){
         TIM_ClearITPendingBit(TIM1,TIM_IT_CC3);
         TIM1_IT_Function();
   } else if(TIM_GetITStatus(TIM1,TIM_IT_CC4) != RESET){
         TIM_ClearITPendingBit(TIM1,TIM_IT_CC4);
         TIM1_IT_Function();
   }
}


void TIM2_IRQHandler(void) {
   if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET){
         TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
         TIM2_IT_Function();
   } else if(TIM_GetITStatus(TIM2,TIM_IT_CC1) != RESET){
            TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
            TIM2_IT_Function();
   } else if(TIM_GetITStatus(TIM2,TIM_IT_CC2) != RESET){
            TIM_ClearITPendingBit(TIM2,TIM_IT_CC2);
            TIM2_IT_Function();
   } else if(TIM_GetITStatus(TIM2,TIM_IT_CC3) != RESET){
            TIM_ClearITPendingBit(TIM2,TIM_IT_CC3);
            TIM2_IT_Function();
   } else if(TIM_GetITStatus(TIM2,TIM_IT_CC4) != RESET){
            TIM_ClearITPendingBit(TIM2,TIM_IT_CC4);
            TIM2_IT_Function();
   }
}


void TIM3_IRQHandler(void) {
   if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET){
         TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
         TIM3_IT_Function();
   } else if(TIM_GetITStatus(TIM3,TIM_IT_CC1) != RESET){
         TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
         TIM3_IT_Function();
   } else if(TIM_GetITStatus(TIM3,TIM_IT_CC2) != RESET){
         TIM_ClearITPendingBit(TIM3,TIM_IT_CC2);
         TIM3_IT_Function();
   } else if(TIM_GetITStatus(TIM3,TIM_IT_CC3) != RESET){
         TIM_ClearITPendingBit(TIM3,TIM_IT_CC3);
         TIM3_IT_Function();
   } else if(TIM_GetITStatus(TIM3,TIM_IT_CC4) != RESET){
         TIM_ClearITPendingBit(TIM3,TIM_IT_CC4);
         TIM3_IT_Function();
   }
}


void TIM4_IRQHandler(void) {
   if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET){
         TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
         TIM4_IT_Function();
   } else if(TIM_GetITStatus(TIM4,TIM_IT_CC1) != RESET){
         TIM_ClearITPendingBit(TIM4,TIM_IT_CC1);
         TIM4_IT_Function();
   } else if(TIM_GetITStatus(TIM4,TIM_IT_CC2) != RESET){
         TIM_ClearITPendingBit(TIM4,TIM_IT_CC2);
         TIM4_IT_Function();
   } else if(TIM_GetITStatus(TIM4,TIM_IT_CC3) != RESET){
         TIM_ClearITPendingBit(TIM4,TIM_IT_CC3);
         TIM4_IT_Function();
   } else if(TIM_GetITStatus(TIM4,TIM_IT_CC4) != RESET){
         TIM_ClearITPendingBit(TIM4,TIM_IT_CC4);
         TIM4_IT_Function();
   }
}


//------- Public functions ------------
/**
* @fn timer_clock_init
* @brief Initializes timers 1, 2, 3 or 4
* @param Timer Timer to be used
* @param period_us Timer period in microseconds  
* @return Period in microseconds obtained
*/
void timer_init (TIM_TypeDef *timer, float period_us){
   volatile const float fclock = (float)SystemCoreClock;
   const float frequency_ratio = SYSTEM_CORE_CLOCK * period_us / US_PER_S;
   float    PSC_val_f, ARR_val_f;
   uint16_t PSC_val  , ARR_val;
   volatile float aux;
   
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   
   // Active la clock
   RCC_timer_configuration(timer);

   // PSC conf
   PSC_val_f = frequency_ratio / ((float)ARR_VALUE_MAX + 1.0) - 1.0;
   PSC_val = (uint16_t)PSC_val_f;                                    // floor
   if((PSC_val_f - (float)PSC_val) > PSC_CEILING_LIMIT) PSC_val++;   // ceiling
   if(PSC_val_f > PSC_VALUE_MAX) PSC_val = PSC_VALUE_MAX;            // saturation
  
   // ARR conf
   ARR_val_f = frequency_ratio / ((float)PSC_val + 1.0) - 1.0;
   ARR_val = (uint16_t)ARR_val_f;                           // floor
   if(ARR_val_f > ARR_VALUE_MAX) ARR_val = ARR_VALUE_MAX;   // saturation
   
  /* set everything back to default values */
  TIM_TimeBaseStructInit (&TIM_TimeBaseStructure);
  /* only changes from the defaults are needed */
  TIM_TimeBaseStructure.TIM_Period = ARR_val;
  TIM_TimeBaseStructure.TIM_Prescaler = PSC_val;
  TIM_TimeBaseInit (timer, &TIM_TimeBaseStructure);


}
 

void timer_start (TIM_TypeDef *timer){
  TIM_Cmd (timer, ENABLE);
}
 

void timer_disable (TIM_TypeDef *timer){
  TIM_Cmd (timer, DISABLE);
}
 


/**
* @fn Timer_1234_ITEnable
* @brief Activates Overflow timer interruption and set function and spriority 
* @param Timer Timer to be used
* @param priority Priority of interruption
* @param IT_function run in interruption handling 
* @return void
*/
void timer_ITEnable(TIM_TypeDef *Timer, uint8_t priority, void (*IT_function)(void)) {
   NVIC_InitTypeDef NVIC_InitStructure;
   IRQn_Type Timer_IRQn;
   
   if (Timer == TIM1) {
      Timer_IRQn = TIM1_UP_IRQn;
      TIM1_IT_Function = IT_function;
   }
   else if (Timer == TIM2) {
      Timer_IRQn = TIM2_IRQn;
      TIM2_IT_Function = IT_function;
   }
   else if (Timer == TIM3) {
      Timer_IRQn = TIM3_IRQn;
      TIM3_IT_Function = IT_function;
   }
   else if (Timer == TIM4) {
      Timer_IRQn = TIM4_IRQn;
      TIM4_IT_Function = IT_function;
   }
   else return;
  
   NVIC_InitStructure.NVIC_IRQChannel = Timer_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
}



/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_timer_configuration(TIM_TypeDef *timer){
       if (timer == TIM1)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  else if (timer == TIM2)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  else if (timer == TIM3)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  else if (timer == TIM4)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
   
}


void Capture_ITEnable(TIM_TypeDef *timer, uint16_t channel, uint8_t priority, void (*IT_function)(void)) {
   NVIC_InitTypeDef NVIC_InitStructure;
   IRQn_Type timer_IRQn;
   
   // Enables the TIMx global Interrupt
   if (timer == TIM1) {
      timer_IRQn = TIM1_UP_IRQn;
      TIM1_IT_Function = IT_function;
   }
   else if (timer == TIM2) {
      timer_IRQn = TIM2_IRQn;
      TIM2_IT_Function = IT_function;
   }
   else if (timer == TIM3) {
      timer_IRQn = TIM3_IRQn;
      TIM3_IT_Function = IT_function;
   }
   else if (timer == TIM4) {
      timer_IRQn = TIM4_IRQn;
      TIM4_IT_Function = IT_function;
   }
   else return;

   /* Enable the TIMx global Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = timer_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   switch(channel){
      case TIM_Channel_1:    TIM_ITConfig(timer, TIM_IT_CC1, ENABLE);    break;
      case TIM_Channel_2:    TIM_ITConfig(timer, TIM_IT_CC2, ENABLE);    break;
      case TIM_Channel_3:    TIM_ITConfig(timer, TIM_IT_CC3, ENABLE);    break;
      case TIM_Channel_4:    TIM_ITConfig(timer, TIM_IT_CC4, ENABLE);    break;
      default : break;
   }
}
