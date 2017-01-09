#include <stdint.h>

#include <stm32f10x.h>

#include "pwm.h"
#include "adc.h"
#include "systick.h"
#include "spi.h"
#include "system_time.h"
#include "hall_sensors.h"
#include "modules_definitions.h"
#include "motors.h"
#include "position_sensors.h"
#include "speed_sensors.h"

void PWM_Example(void);
void ADC_Example(void);
void HallSensor_Example(HallSensors_Enum hall_identifier);
void Motor_Example(Motors_Enum Motor);
void PositionSensor_Example(PositionSensor_Enum PositionSensor_identifier);
void SpeedSensor_Example(SpeedSensor_Enum SpeedSensor_identifier);

// MAIN POUR DEMO BAS NIVEAU
//int main(void) {
////    SysTick_QuickInit();
//    
////    PWM_Example();
//    
////    ADC_Example();

////    SPI_QuickInit(*SPI1, SPI_Mode_Slave);
//    while (1) {}
//}

int main (void) {
    
    //HallSensor_Example(HALLSENSOR_L);
    Motor_Example(REAR_MOTOR_R);
    //PositionSensor_Example(POSITION_SENSOR_L);
    //SpeedSensor_Example(POSITION_SENSOR_L);
    while (1) {}
}

/**
 * @brief 	Sets PWM output on PA8 and its complementary on PB13. PWMs frequency is 1 kHz. Duty cycle on PA8 is 0.75.
 * @retval 	None
*/
void PWM_Example(void) {
    PWM_QuickInit(TIM1, TIM_Channel_1, 1000.0);         // Output on PA8
    PWM_QuickInit_Complementary(TIM1, TIM_Channel_1);   // Output on PB13
    
    PWM_SetDutyCycle(TIM1, TIM_Channel_1, 0.75);
    PWM_Start(TIM1);
}

/**
 * @brief 	Sets PA0 as analog input
 * @retval 	None
*/
void ADC_Example(void) {
    ADC_QuickInit(ADC1, GPIOA, GPIO_Pin_0, 0, ADC_SampleTime_71Cycles5);
}

/**
 * @brief   Lauches hall sensor. After this procedure, hall-sensor interrupts detected. Best way to see it is to run debug mode and insert a breakpoint in the function HallSensor_EdgeCallback().
 * @param   hall_identifier Hall Sensor to be considered
 * @retval  None
*/
void HallSensor_Example(HallSensors_Enum hall_identifier) {
    HallSensor_QuickInit(hall_identifier);
}

/**
 * @brief   Lauches motor. Motor is initalized, then set to forward 80% during 3 seconds, 
                                                then stoped during 3seconds,
                                                then set to backward 80% during 3 seconds,
                                                and finally stoped.
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void Motor_Example(Motors_Enum Motor) {
    System_Time_QuickInit();
    Motor_QuickInit(Motor);
    Motor_Enable(Motor);
    
    Motor_setSpeed(Motor, 0.80);
    pause(1000*3);
    Motor_setSpeed(Motor, 0.00);
    pause(1000*3);
    Motor_setSpeed(Motor, -0.80);
    pause(1000*3);
    
    Motor_Disable(Motor);
}

/**
 * @brief   Measures car position. 
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void PositionSensor_Example(PositionSensor_Enum PositionSensor_identifier) {
    float WheelPosition = 0; 
    
    System_Time_QuickInit();
    PositionSensor_QuickInit(PositionSensor_identifier); 
    
    while(1) {
        pause(100); 
        WheelPosition = PositionSensor_get(POSITION_M_, PositionSensor_identifier);
    }
    
}

/**
 * @brief   Measures car speed. 
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void SpeedSensor_Example(SpeedSensor_Enum SpeedSensor_identifier) {
    float WheelSpeed = 0; 
    
    System_Time_QuickInit();
    PositionSensor_QuickInit(SpeedSensor_identifier); 
    
    while(1) {
        pause(100); 
        WheelSpeed = SpeedSensor_get(SPEED_M__S, SpeedSensor_identifier);
    }
}
