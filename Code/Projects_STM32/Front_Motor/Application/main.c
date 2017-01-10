#include <stdint.h>
#include <stm32f10x.h>
#include <exti.h>
#include <motor.h>
#include <front_motor.h>
#include "stm32f10x_it.h"



int main(void) {
	
    front_motor_QuickInit();
 
//    front_motor_turn(RIGHT);
//    front_motor_stop();
//    front_motor_turn(LEFT);
//    front_motor_stop();
//    front_motor_turn(LEFT);
//    front_motor_turn(RIGHT);
//    front_motor_turn(LEFT); 
    while(1){
//EXTI_GenerateSWInterrupt(FRONT_LINE_LEFT);
        
    }
   return 0;
}

//ENABLE:¡PPB2
//PWM IN1 : PA10 IN2 = PB1
//info_buteeAV_G = EXTI PC10
//info_buteeAV_D = EXTI PC11
//Timer : TIM1 TIM_Channel_3 

