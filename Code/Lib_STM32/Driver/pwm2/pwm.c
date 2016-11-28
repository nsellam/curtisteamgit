#include <pwm.h>


void capture_imput_init(TIM_TypeDef* timer, uint16_t channel, float period_us){
  /* TIM3 configuration: Input Capture mode ---------------------
     The external signal is connected to TIM3 CH2 pin (PA.07)  
     The Rising edge is used as active edge,
     The TIM3 CCR2 is used to compute the frequency value 
  ------------------------------------------------------------ */
   TIM_ICInitTypeDef  TIM_ICInitStructure;
   
   //Timer_1234_Init(timer, period_us);
     
   if(channel == 1)      TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
   else if(channel == 2) TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
   else if(channel == 3) TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
   else if(channel == 4) TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
   
   TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
   TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
   TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
   TIM_ICInitStructure.TIM_ICFilter = 0x00;
   TIM_ICInit(timer, &TIM_ICInitStructure);
}



void capture_imput_start(TIM_TypeDef* timer, uint16_t channel){
   /* Enable the CCx Interrupt Request */
   if(channel == 1)      TIM_ITConfig(timer, TIM_IT_CC1, ENABLE);
   else if(channel == 2) TIM_ITConfig(timer, TIM_IT_CC2, ENABLE);
   else if(channel == 3) TIM_ITConfig(timer, TIM_IT_CC3, ENABLE);
   else if(channel == 4) TIM_ITConfig(timer, TIM_IT_CC4, ENABLE);
   
   /* TIM enable counter */
   TIM_Cmd(timer, ENABLE);


}
