/* MODIFIED SYSTEM_TIME FOR LOW LEVEL EXAMPLES */ 
/* This version of system_time.h must only be used when performing the examples below : */
    //ADC_Diagnoser();              
    //GPIO_Diagnoser();             
    //PWM_Diagnoser();              
    //Motor_Diagnoser();
    //Battery_Diagnoser(); 
    //HallSensor_Diagnoser(); 
                                
/**
 * @file    system_time.h
 * @author  Curtis Team
 * @brief   Headers of functions to manage time
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SYSTEM_TIME_H
#define _SYSTEM_TIME_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void System_Time_QuickInit(void);

void SysTick_Callback(void);

uint64_t millis(void);

void pause(uint16_t ms);

#endif // _SYSTEM_TIME_H
