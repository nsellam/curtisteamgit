
#include "ultrasonic.h"

int main(){

   volatile float aux, i;
   
   Ultrasonic_Init();

   Ultrasonic_Start();

   while(1){
      for(i=0; i<10e5; i++)
      aux = Ultrasonic_GetDistance();
   }
   return 0;
}
