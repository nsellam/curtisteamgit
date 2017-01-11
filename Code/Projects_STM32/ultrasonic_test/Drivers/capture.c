#include "capture.h"
#include "timer.h"

__weak void Ultrasonic_ITHandler(TIM_TypeDef *timer, uint16_t channel) {}

    
void TIM1_IT_Callback(uint16_t channel) {
    Ultrasonic_ITHandler(TIM1, channel);
}    
    
void TIM2_IT_Callback(uint16_t channel) {
    Ultrasonic_ITHandler(TIM2, channel);
}


void TIM3_IT_Callback(uint16_t channel) {
    Ultrasonic_ITHandler(TIM3, channel);
}



void TIM4_IT_Callback(uint16_t channel) {
    Ultrasonic_ITHandler(TIM4, channel);
}



void Capture_Init(TIM_TypeDef *timer, uint16_t channel, float frequency_compare_Hz){  
   static int init = 0;
   float duree_compare_usec = US_PER_S/frequency_compare_Hz;
   TIM_ICInitTypeDef  TIM_ICInitStructure;
   if(!init){
    init = 1;
       timer_init(timer, duree_compare_usec);
   }
  
   TIM_ICInitStructure.TIM_Channel = channel;
   TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
   TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
   TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
   TIM_ICInitStructure.TIM_ICFilter = 0x0;
  
   TIM_ICInit(timer, &TIM_ICInitStructure);
}

void Capture_Enable(TIM_TypeDef *timer){
   timer_start(timer); 
}


void Capture_Disable(TIM_TypeDef *timer){
   timer_disable(timer);  
}


void Capture_PortInit(TIM_TypeDef *timer, uint16_t channel) {
   if (timer == TIM1) {
      switch (channel) {
         case TIM_Channel_1: GPIO_QuickInit(GPIOA, GPIO_Pin_8 , CAPTURE_GPIO_MODE); break;
         case TIM_Channel_2: GPIO_QuickInit(GPIOA, GPIO_Pin_9 , CAPTURE_GPIO_MODE); break;
         case TIM_Channel_3: GPIO_QuickInit(GPIOA, GPIO_Pin_10, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_4: GPIO_QuickInit(GPIOA, GPIO_Pin_11, CAPTURE_GPIO_MODE); break;
         default: break;
      }
   }
   else if (timer == TIM2) {
      switch (channel) {
         case TIM_Channel_1: GPIO_QuickInit(GPIOA, GPIO_Pin_0, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_2: GPIO_QuickInit(GPIOA, GPIO_Pin_1, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_3: GPIO_QuickInit(GPIOA, GPIO_Pin_2, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_4: GPIO_QuickInit(GPIOA, GPIO_Pin_3, CAPTURE_GPIO_MODE); break;
         default: break;
      }
   }
   else if (timer == TIM3) {
      switch (channel) {
         case TIM_Channel_1: GPIO_QuickInit(GPIOA, GPIO_Pin_6, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_2: GPIO_QuickInit(GPIOA, GPIO_Pin_7, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_3: GPIO_QuickInit(GPIOB, GPIO_Pin_0, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_4: GPIO_QuickInit(GPIOB, GPIO_Pin_1, CAPTURE_GPIO_MODE); break;
         default: break;
      }
   }
   else if (timer == TIM4) {
      switch (channel) {
         case TIM_Channel_1: GPIO_QuickInit(GPIOB, GPIO_Pin_6, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_2: GPIO_QuickInit(GPIOB, GPIO_Pin_7, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_3: GPIO_QuickInit(GPIOB, GPIO_Pin_8, CAPTURE_GPIO_MODE); break;
         case TIM_Channel_4: GPIO_QuickInit(GPIOB, GPIO_Pin_9, CAPTURE_GPIO_MODE); break;
         default: break;
      }
   }

}

void Capture_ITEnable(TIM_TypeDef *timer, uint16_t channel, uint8_t priority) {
   NVIC_InitTypeDef NVIC_InitStructure;
   IRQn_Type timer_IRQn;
   
   // Enables the TIMx global Interrupt
   if (timer == TIM1) {
      timer_IRQn = TIM1_UP_IRQn;
   }
   else if (timer == TIM2) {
      timer_IRQn = TIM2_IRQn;
   }
   else if (timer == TIM3) {
      timer_IRQn = TIM3_IRQn;
   }
   else if (timer == TIM4) {
      timer_IRQn = TIM4_IRQn;
   }
   else return;

   NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);
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




