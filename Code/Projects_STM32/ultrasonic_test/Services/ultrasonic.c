
#include "ultrasonic.h"

#define FILTER_SIZE 5
#define ULTRASONIC_SENSORS 6
#define PWM_PERIOD_US 250e3
#define PWM_FREQUENCY US_PER_S/PWM_PERIOD_US
#define TRIGGER_DC 1.0e-4
#define AUXILIARY_VAR  (0.5/0.137)*(23/83.53)   // (124.0e3/22.88)
#define ULTRASSONIC_PARAMETER 10.0/2.5e4//(10.0/594.0)/160
#define ULTRASONIC_SATURATION 400.0
#define ULTRASONIC_SATURATION_DELTA 10.0


float PeriodUs[ULTRASONIC_SENSORS] = {0,0,0,0,0,0};
uint8_t Distance[ULTRASONIC_SENSORS] = {0,0,0,0,0,0};
int CaptureITAux[ULTRASONIC_SENSORS] = {0,0,0,0,0,0};
uint16_t CaptureValRisingEdge[6]  = {0,0,0,0,0,0};
uint16_t CaptureValFallingEdge[6] = {0,0,0,0,0,0};
float FilterVector[ULTRASONIC_SENSORS][FILTER_SIZE];
uint8_t CapturePriority[ULTRASONIC_SENSORS] = {1,2,3,4,5,6};
int VariableAux;




//------- Private functions ----------


// Private prototypes
void  FilterInit(void);
float UltrasonicFilter(float mesure);


void Ultrasonic_ITHandler(TIM_TypeDef *timer, uint16_t channel){
    
    if (timer == TIM2) {
      switch(channel){
         case TIM_Channel_2:  VariableAux = 0;      break;  
         case TIM_Channel_3:  VariableAux = 1;      break;  
         case TIM_Channel_4:  VariableAux = 2;      break;  
         default:    break;
      }
    } else if (timer == TIM3) {
      switch(channel){
         case TIM_Channel_2:  VariableAux = 3;      break;  
         case TIM_Channel_3:  VariableAux = 4;      break;  
         case TIM_Channel_4:  VariableAux = 5;      break;  
         default:    break;
      }
    }
    if ( CaptureITAux[VariableAux] == 0 ){
       
          switch(channel){
             case TIM_Channel_2:  CaptureValRisingEdge[VariableAux] = TIM_GetCapture2(timer);      break;  
             case TIM_Channel_3:  CaptureValRisingEdge[VariableAux] = TIM_GetCapture3(timer);      break;  
             case TIM_Channel_4:  CaptureValRisingEdge[VariableAux] = TIM_GetCapture4(timer);      break;  
             default:    break;
         }
         TIM_OC2PolarityConfig(timer,TIM_ICPolarity_Falling);
         CaptureITAux[VariableAux] = 1;        
   }
   else if ( CaptureITAux[VariableAux] == 1 ){
       
         switch(channel){
             case TIM_Channel_2:  CaptureValFallingEdge[VariableAux] = TIM_GetCapture2(timer);      break;  
             case TIM_Channel_3:  CaptureValFallingEdge[VariableAux] = TIM_GetCapture3(timer);      break;  
             case TIM_Channel_4:  CaptureValFallingEdge[VariableAux] = TIM_GetCapture4(timer);      break;  
             default:    break;
         }
         TIM_OC2PolarityConfig(timer,TIM_ICPolarity_Rising);
         CaptureITAux[VariableAux] = 0;
         
         if( CaptureValFallingEdge[VariableAux] <= CaptureValRisingEdge[VariableAux] )
            PeriodUs[VariableAux] =  (float) ((CaptureValRisingEdge[VariableAux] - CaptureValFallingEdge[VariableAux])*AUXILIARY_VAR*PWM_PERIOD_US)/65535.0;
         else
            PeriodUs[VariableAux] =  (float) (((0xFFFF - CaptureValFallingEdge[VariableAux] + 1) + CaptureValRisingEdge[VariableAux])*AUXILIARY_VAR*PWM_PERIOD_US)/65535.0;
            
         //Distance[VariableAux] = (uint8_t) (UltrasonicFilter(PeriodUs[VariableAux]*ULTRASSONIC_PARAMETER));
         Distance[VariableAux] = (uint8_t) PeriodUs[VariableAux]; 
   }
}


float UltrasonicFilter(float mesure){ 
   int i;
   float sum = 0;
   
   // Saturation
   if( mesure<= ULTRASONIC_SATURATION ){
      for(i=1; i<FILTER_SIZE; i++ )
         FilterVector[VariableAux][i] = FilterVector[VariableAux][i-1];
      FilterVector[VariableAux][0] = mesure;
      
      //FIR filter of 5th order
      for(i=0; i<FILTER_SIZE; i++ )
        sum = sum + FilterVector[VariableAux][i];
       
      return sum/5;
   } else
      return ULTRASONIC_SATURATION;
}


void FilterInit(void){
    int i,j;
    for(i=0; i<ULTRASONIC_SENSORS; i++)
        for(j=0; j<FILTER_SIZE; j++)
            FilterVector[i][j] = 0;
}


//------- Public functions ------------
void Ultrasonic_Init(void) {
   
   FilterInit(); 
   
   pwm_init(US_F_TIMx ,US_F_TRIG_CH,PWM_FREQUENCY);
   pwm_init(US_R_TIMx ,US_R_TRIG_CH,PWM_FREQUENCY); 
   
   pwm_port_init(US_F_TIMx, US_F_TRIG_CH);
   pwm_port_init(US_R_TIMx, US_R_TRIG_CH); 

   pwm_set_duty_cycle(US_F_TIMx, US_F_TRIG_CH, TRIGGER_DC);
   pwm_set_duty_cycle(US_R_TIMx, US_R_TRIG_CH, TRIGGER_DC); 
   
   Capture_Init(US_F_TIMx, US_FR_ECHO_CH, PWM_FREQUENCY);
   Capture_Init(US_F_TIMx, US_FM_ECHO_CH, PWM_FREQUENCY);
   Capture_Init(US_F_TIMx, US_FL_ECHO_CH, PWM_FREQUENCY);
   Capture_Init(US_R_TIMx, US_RR_ECHO_CH, PWM_FREQUENCY);
   Capture_Init(US_R_TIMx, US_RM_ECHO_CH, PWM_FREQUENCY);
   Capture_Init(US_R_TIMx, US_RL_ECHO_CH, PWM_FREQUENCY); 
        
   Capture_PortInit(US_F_TIMx, US_FR_ECHO_CH);
   Capture_PortInit(US_F_TIMx, US_FM_ECHO_CH);
   Capture_PortInit(US_F_TIMx, US_FL_ECHO_CH);
   Capture_PortInit(US_R_TIMx, US_RR_ECHO_CH);
   Capture_PortInit(US_R_TIMx, US_RM_ECHO_CH);
   Capture_PortInit(US_R_TIMx, US_RL_ECHO_CH); 
}


void Ultrasonic_Start(void) {
   Capture_ITEnable(US_F_TIMx, US_FR_ECHO_CH, CapturePriority[0]);
   Capture_ITEnable(US_F_TIMx, US_FM_ECHO_CH, CapturePriority[1]);
   Capture_ITEnable(US_F_TIMx, US_FL_ECHO_CH, CapturePriority[2]);
   Capture_ITEnable(US_R_TIMx, US_RR_ECHO_CH, CapturePriority[3]);
   Capture_ITEnable(US_R_TIMx, US_RM_ECHO_CH, CapturePriority[4]);
   Capture_ITEnable(US_R_TIMx, US_RL_ECHO_CH, CapturePriority[5]);
   
   Capture_Enable(US_F_TIMx);
   Capture_Enable(US_R_TIMx); 
}


void Ultrasonic_Stop(void) {
   Capture_Disable(US_F_TIMx);
   Capture_Disable(US_R_TIMx); 
}


float Ultrasonic_GetDistance(TIM_TypeDef *timer, uint16_t channel){
    
    if (timer == TIM2) {
      switch(channel){
         case TIM_Channel_2:  VariableAux = 0;      break;  
         case TIM_Channel_3:  VariableAux = 1;      break;  
         case TIM_Channel_4:  VariableAux = 2;      break;  
         default:    break;
      }
   } else if (timer == TIM3) {
      switch(channel){
         case TIM_Channel_2:  VariableAux = 3;      break;  
         case TIM_Channel_3:  VariableAux = 4;      break;  
         case TIM_Channel_4:  VariableAux = 5;      break;  
         default:    break;
      }
   }
    
   return Distance[VariableAux];
}
