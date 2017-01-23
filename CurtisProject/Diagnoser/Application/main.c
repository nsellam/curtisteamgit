#include <stdint.h>
#include <stm32f10x.h>

#include "examples.h"

int main(void) { 
    //ADC_Diagnoser();              // You need to connect all the ADC pins together
    //GPIO_Diagnoser();               // You need to connect the GPIO to diagnose together
    //PWM_Diagnoser();              // Diagnosis must be done in simulation mode only
    Motor_Diagnoser();
    //Battery_Diagnoser(); 
    //HallSensor_Diagnoser();       // Diagnosis is done by adding a breakpoint in HallSensor_Handler()
    while(1) {}
}
