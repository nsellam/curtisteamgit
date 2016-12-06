#include <stdint.h>
#include <stm32f10x.h>
#include <adc.h>
#include <systick.h>
#include <motor.h>
#include <pwm.h>

int i =0;
	uint64_t t = 0;
	uint64_t t_exp = 50;
	uint16_t tableau_ADC_moteur_D[100];
	uint16_t tableau_ADC_moteur_G[100];
	
int main(void) {
	// volatile int aux = 0;
   volatile float speed = 0.8;
   
   motors_init();
	//Init ADC1 with channel_0 => PA0 and channel_1 => PA1
	//ADC Values are strocked in variable 'ADC_Value'
	 Init_ADC(GPIOA,GPIO_Pin_0,GPIOA,GPIO_Pin_1,ADC1,ADC_Channel_0,ADC_Channel_1,ADC_SampleTime_71Cycles5,DMA1_Channel1); 
	 systick_init();
	
	// Start motor
	 motor_set_speed(speed);
   motors_start();

	do{
		if(micros() - t > t_exp){
			t = micros();
			tableau_ADC_moteur_D[i] = Get_ADC_Mot_D();
			tableau_ADC_moteur_G[i] = Get_ADC_Mot_G();
			i++;
		}
	}while(i<100);
	
	while(1){}
   return 0;
}

