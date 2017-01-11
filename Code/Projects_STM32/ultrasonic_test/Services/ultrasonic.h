
#ifndef _Ultrasonic_H_
#define _Ultrasonic_H_

/********************************/
/*         LIBRARIES            */
/********************************/
#include <stdint.h>
#include <math.h>

#include <stm32f10x.h>
#include "pwm.h"
#include "capture.h"


/********************************/
/*          CONSTANTS           */
/********************************/
#define US_MAX_VALUE 16


/********************************/
/*           STRUCTS            */
/********************************/
typedef struct {
   uint8_t NumSensor;
   TIM_TypeDef *TIMx;
   uint16_t TriggerChannel;
   uint16_t EchoChannel;
   uint8_t ITPriority;
   
   float Distance;
   float PeriodUs;
   float FilterVector[5];
   uint16_t CaptureValRisingEdge;
   uint16_t CaptureValFallingEdge;
   int CaptureITAux;
   } Ultrasonic; 


   #define US_FR_NUM 0x00
   #define US_FM_NUM 0x01
   #define US_FL_NUM 0x02
   #define US_RR_NUM 0x03
   #define US_RM_NUM 0x04
   #define US_RL_NUM 0x05

   #define US_F_TIMx       TIM2
   #define US_F_TRIG_CH    TIM_Channel_1
   #define US_FR_ECHO_CH   TIM_Channel_2
   #define US_FM_ECHO_CH   TIM_Channel_3
   #define US_FL_ECHO_CH   TIM_Channel_4

   #define US_R_TIMx       TIM3
   #define US_R_TRIG_CH    TIM_Channel_1
   #define US_RR_ECHO_CH   TIM_Channel_2
   #define US_RM_ECHO_CH   TIM_Channel_3
   #define US_RL_ECHO_CH   TIM_Channel_4
       
/********************************/
/*         FUNCTIONS            */
/********************************/   
//void Ultrasonic_Init(Ultrasonic* Sensor);

//void Ultrasonic_Start(Ultrasonic* Sensor);

//void Ultrasonic_Stop(Ultrasonic* Sensor);

//uint8_t Ultrasonic_GetDistance(Ultrasonic* Sensor);

   
void Ultrasonic_Init(void);

void Ultrasonic_Start(void);

void Ultrasonic_Stop(void);

float Ultrasonic_GetDistance(TIM_TypeDef *timer, uint16_t channel);   
   
#endif // _Ultrasonic_H_

