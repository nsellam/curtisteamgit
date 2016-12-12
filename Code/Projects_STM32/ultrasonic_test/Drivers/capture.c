#include "capture.h"
#include "timer.h"


void Capture_Init(TIM_TypeDef *timer, uint16_t channel, float frequency_compare_Hz){  
   float duree_compare_usec = US_PER_S/frequency_compare_Hz;
   TIM_ICInitTypeDef  TIM_ICInitStructure;
   
   timer_init(timer, duree_compare_usec);
  
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




