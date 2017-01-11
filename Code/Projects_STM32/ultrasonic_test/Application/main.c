
#include "ultrasonic.h"

int main(){

   int i;
   volatile float  aux[6]; 
   
   Ultrasonic_Init();
   Ultrasonic_Start();

   while(1){
      for(i=0; i<1e5; i++);
      aux[0] = Ultrasonic_GetDistance(US_F_TIMx, US_FR_ECHO_CH);
      aux[1] = Ultrasonic_GetDistance(US_F_TIMx, US_FM_ECHO_CH);
      aux[2] = Ultrasonic_GetDistance(US_F_TIMx, US_FL_ECHO_CH);
      aux[3] = Ultrasonic_GetDistance(US_R_TIMx, US_RR_ECHO_CH);
      aux[4] = Ultrasonic_GetDistance(US_R_TIMx, US_RM_ECHO_CH);
      aux[5] = Ultrasonic_GetDistance(US_R_TIMx, US_RL_ECHO_CH);  
   }
   return 0;
}
