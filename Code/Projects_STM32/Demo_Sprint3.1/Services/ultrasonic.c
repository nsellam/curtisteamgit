

#include "ultrasonic.h"


#define TIMx TIM2
#define CH_TRIGGER TIM_Channel_1
#define CH_ECHO TIM_Channel_2
#define PWM_PERIOD_US 250e3
#define PWM_FREQUENCY US_PER_S/PWM_PERIOD_US
#define TRIGGER_DC 0.0001
#define CAPTURE_PRIORITY 3
#define AUXILIARY_VAR  (0.5/0.137)*(23/83.53)   // (124.0e3/22.88)
#define ULTRASSONIC_PARAMETER (10.0/594.0)   //(58.2*(6.0/16.0)*(6/6.5))
#define ULTRASONIC_SATURATION 400.0
#define ULTRASONIC_SATURATION_DELTA 10.0

volatile float period_us;
uint8_t distance_cm;
int capture_IT_aux_var = 0;
uint16_t capture_val_rising_edge, capture_val_falling_edge;
float filter[5]={0,0,0,0,0};




//------- Private functions ----------


// Private prototypes
float Ultrasonic_Filter(float mesure);


void Ultrasonic_ITHandling(uint16_t channel){
   
   if (capture_IT_aux_var == 0){
         capture_val_rising_edge = TIM_GetCounter(TIMx);
         TIM_OC2PolarityConfig(TIMx,TIM_ICPolarity_Falling);
         capture_IT_aux_var = 1;        
   }
   else if (capture_IT_aux_var == 1){
         capture_val_falling_edge = TIM_GetCounter(TIMx);
         TIM_OC2PolarityConfig(TIMx,TIM_ICPolarity_Rising);
         capture_IT_aux_var = 0;
         
         if( capture_val_falling_edge >= capture_val_rising_edge)
            period_us = ( (float) (capture_val_falling_edge - capture_val_rising_edge)*AUXILIARY_VAR*PWM_PERIOD_US)/65535.0;
         else
            period_us = ( (float) ((0xFFFF + capture_val_falling_edge + 1) - capture_val_rising_edge)*AUXILIARY_VAR*PWM_PERIOD_US)/65535.0;
            
         distance_cm = (uint8_t) (Ultrasonic_Filter(period_us*ULTRASSONIC_PARAMETER));       
   }
}


float Ultrasonic_Filter(float mesure){ 
   int i;
   
   // Saturation
   if( mesure<= ULTRASONIC_SATURATION ){
      for(i=1; i<5; i++ )
         filter[i] = filter[i-1];
      filter[0] = mesure;
      
      //FIR filter of 5th order 
      return (filter[0] + filter[1] + filter[2] + filter[3] + filter[4])/5;
   } else
      return ULTRASONIC_SATURATION;
}


//------- Public functions ------------
void Ultrasonic_Init(void) {
   pwm_init(TIMx,CH_TRIGGER,PWM_FREQUENCY);
   pwm_port_init(TIMx, CH_TRIGGER);
   
   pwm_set_duty_cycle(TIMx, CH_TRIGGER, TRIGGER_DC);
   
   Capture_Init(TIMx, CH_ECHO, PWM_FREQUENCY);
   Capture_PortInit(TIMx, CH_ECHO);
   
}


void Ultrasonic_Start(void) {
   Capture_ITEnable(TIMx, CH_ECHO, CAPTURE_PRIORITY);
   Capture_Enable(TIMx);
}

void Ultrasonic_Stop(void) {
   Capture_Disable(TIMx);
}


float Ultrasonic_GetDistance(){
   return distance_cm;
}
