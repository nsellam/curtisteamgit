#include <stdint.h>

#include <stm32f10x.h>

#include "pwm.h"
#include "adc.h"
#include "gpio.h"
#include "systick.h"
#include "spi.h"
#include "system_time.h"
#include "hall_sensors.h"
#include "modules_definitions.h"
#include "motors.h"
#include "position_sensors.h"
#include "speed_sensors.h"
#include "front_motor.h"
#include "rear_motors.h"

void PWM_Example(void);
void ADC_Example(void);
void HallSensor_Example(HallSensors_Enum hall_identifier);
void Motor_Example(Motors_Enum Motor);
void PositionSensor_Example(PositionSensor_Enum PositionSensor_identifier);
void SpeedSensor_Example(SpeedSensor_Enum SpeedSensor_identifier);
void GPIO_Example(void);
void RearMotors_Example(void);

// MAIN POUR DEMO BAS NIVEAU
//int main(void) {
//    SysTick_QuickInit();
    
//    PWM_Example();
    
//    ADC_Example();

//    SPI_QuickInit(*SPI1, SPI_Mode_Slave);
//    while (1) {}
//}

int main (void) {
    
    //HallSensor_Example(HALLSENSOR_L);
    //Motor_Example(REAR_MOTOR_L);
    //GPIO_Example();
    //PWM_Example();
    //PositionSensor_Example(POSITION_SENSOR_L);
    //SpeedSensor_Example(SPEED_SENSOR_L);
    //PWM_Example();
    RearMotors_Example();
    while (1) {}
}

/**
 * @brief 	Sets PC13 to '1'
 * @retval 	None
*/
void GPIO_Example(void) {
    GPIO_QuickInit(GPIOC, GPIO_Pin_13, GPIO_Mode_Out_PP);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

/**
 * @brief 	Sets PWM output on PA8 and its complementary on PB13. PWMs frequency is 1 kHz. Duty cycle on PA8 is 0.75.
 * @retval 	None
*/
void PWM_Example(void) {

    PWM_QuickInit(TIM1, TIM_Channel_1, 20000.0);         // Output on PA8
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
    PWM_QuickInit_Complementary(TIM1, TIM_Channel_1);   // Output on PB13
    
    PWM_SetDutyCycle(TIM1, TIM_Channel_1, 0.250);
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
    
    Motor_setSpeed(Motor, 1.0);
    pause(1000*3);
    Motor_setSpeed(Motor, 0.0);
    pause(1000*3);
    Motor_setSpeed(Motor, -1.0);
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
    
    while(WheelSpeed >= 0) {
        pause(100); 
        WheelSpeed = SpeedSensor_get(SPEED_M__S, SpeedSensor_identifier);
    }
}

/**
 * @brief   Tests front motor by turning left, expecting 1 second and turning right. 
 * @retval  None
*/
void FrontMotor_Example(void) {
    System_Time_QuickInit();
    FrontMotor_QuickInit();
    while(1) {
        FrontMotor_turn(LEFT); 
        pause(3000);
        FrontMotor_turn(RIGHT);
        pause(3000);
    }
}

void RearMotors_Example(void) {
    Motor_QuickInit(REAR_MOTOR_L);
    System_Time_QuickInit();
    SpeedSensor_QuickInit(SPEED_SENSOR_L);
    Motor_Enable(REAR_MOTOR_L);
}
