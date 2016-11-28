#ifndef _GPIO2_H_
#define _GPIO2_H_

#include <stdint.h>
#include <stm32f10x.h>

// Active la clock du GPIO
void Port_IO_Clock_Enable(GPIO_TypeDef* GPIOx);

// Permet de configurer une broche d'un port en output push-pull 50MHz
int Port_IO_Init_Output(GPIO_TypeDef* GPIOx, uint8_t broche);

// Permet de configurer une broche d'un port en alternate function output push-pull 50MHz
int Port_IO_Init_Output_AltFunct(GPIO_TypeDef* GPIOx, uint8_t broche);

// Permet de configurer une broche d'un port en floating input
int Port_IO_Init_Input(GPIO_TypeDef* GPIOx, uint8_t broche);

// Permet de configurer une broche d'un port en analog input
int Port_IO_Init_Input_Analog(GPIO_TypeDef* GPIOx, uint8_t broche);


// Permet de mettre à 1 une broche d'un port
void Port_IO_Set(GPIO_TypeDef* GPIOx, uint8_t broche);

// Permet de mettre à 0 une broche d'un port
void Port_IO_Reset(GPIO_TypeDef* GPIOx, uint8_t broche);

// Inverse l'état d'une broche
void Port_IO_Blink(GPIO_TypeDef* GPIOx, uint8_t broche);

// Permet de lire l'état d'une broche d'un port
uint16_t Port_IO_Read(GPIO_TypeDef* GPIOx, uint8_t broche);

void RCC_GPIO_configuration(GPIO_TypeDef* GPIOx);

//void GPIO_AFIO_input(GPIO_TypeDef* GPIOx, uint8_t pin, GPIOSpeed_TypeDef speed);

#endif // _GPIO_H_
