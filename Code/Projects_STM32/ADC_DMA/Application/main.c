#include <stdint.h>
#include <stm32f10x.h>
#include <adc.h>

int main(void) {

	//Init ADC1 with channel_0 => PA0 and channel_1 => PA1
	//ADC Values are strocked in variable 'ADC_Value'
	 Init_ADC(GPIOA,GPIO_Pin_0,GPIOA,GPIO_Pin_1,ADC1,ADC_Channel_0,ADC_Channel_1,ADC_SampleTime_71Cycles5,DMA1_Channel1); 
	
	
	while(1){
	}
   return 0;
}

