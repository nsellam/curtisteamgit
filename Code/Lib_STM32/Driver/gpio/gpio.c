#include "gpio.h"

#include <stdint.h>
#include <stm32f10x.h>


//------- Private prototypes ----------
static int Port_IO_Init(GPIO_TypeDef* GPIOx, uint8_t broche, uint8_t config);


//------- Public functions ------------
// Active la clock du GPIO
void Port_IO_Clock_Enable(GPIO_TypeDef* GPIOx) {
   if (GPIOx == GPIOA)
      RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
   else if (GPIOx == GPIOB)
      RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
   else if (GPIOx == GPIOC)
      RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
   else if (GPIOx == GPIOD)
      RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
}

// Permet de configurer une broche d'un port en output push-pull 50MHz
int Port_IO_Init_Output(GPIO_TypeDef* GPIOx, uint8_t broche) {
   return Port_IO_Init(GPIOx, broche, 0x3);
}

// Permet de configurer une broche d'un port en alternate function output push-pull 50MHz
int Port_IO_Init_Output_AltFunct(GPIO_TypeDef* GPIOx, uint8_t broche) {
   return Port_IO_Init(GPIOx, broche, 0xB);
}

// Permet de configurer une broche d'un port en floating input
int Port_IO_Init_Input(GPIO_TypeDef* GPIOx, uint8_t broche) {
   return Port_IO_Init(GPIOx, broche, 0x4);
}

// Permet de configurer une broche d'un port en analog input
int Port_IO_Init_Input_Analog(GPIO_TypeDef* GPIOx, uint8_t broche) {
   return Port_IO_Init(GPIOx, broche, 0x0);
}


// Permet de mettre à 1 une broche d'un port
void Port_IO_Set(GPIO_TypeDef* GPIOx, uint8_t broche) {
   GPIOx->BSRR = (1 << broche);
}

// Permet de mettre à 0 une broche d'un port
void Port_IO_Reset(GPIO_TypeDef* GPIOx, uint8_t broche) {
   GPIOx->BRR = (1 << broche);
}

// Inverse l'état d'une broche
void Port_IO_Blink(GPIO_TypeDef* GPIOx, uint8_t broche) {
   GPIOx->ODR ^= (1 << broche);
}

// Permet de lire l'état d'une broche d'un port
uint16_t Port_IO_Read(GPIO_TypeDef* GPIOx, uint8_t broche) {
   return GPIOx->IDR & (1 << broche);
}


//------- Private functions -----------
int Port_IO_Init(GPIO_TypeDef* GPIOx, uint8_t broche, uint8_t config) {
   int erreur = 0;
   if (broche < 8) {
      GPIOx->CRL &= ~(0xF << broche*4); // clear MODEy et CNFy
      GPIOx->CRL |= ((config & 0xF) << broche*4);
   } else if (broche < 16) {
      GPIOx->CRH &= ~(0xF << (broche-8)*4); // clear MODEy et CNFy
      GPIOx->CRH |= ((config & 0xF) << (broche-8)*4);
   } else
      erreur = 1;
   return erreur;
}


/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_GPIO_configuration(GPIO_TypeDef* GPIOx)
{
  if (GPIOx == GPIOA)       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  else if (GPIOx == GPIOB)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  else if (GPIOx == GPIOC)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  else if (GPIOx == GPIOD)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
}

/**
  * @brief  Configure the GPIOD Pins.
  * @param  None
  * @retval None
  */
/*void GPIO_AFIO_input(GPIO_TypeDef* GPIOx, uint8_t pin, GPIOSpeed_TypeDef speed)
{
   GPIO_InitTypeDef GPIO_InitStructure;

   // TIM3 channel 2 pin (PA.07) configuration
   
   if(pin == 0)       GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
   else if(pin == 1)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
   else if(pin == 2)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
   else if(pin == 3)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
   else if(pin == 4)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
   else if(pin == 5)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
   else if(pin == 6)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
   else if(pin == 7)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
   else if(pin == 8)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
   else if(pin == 9)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
   else if(pin == 10) GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
   else if(pin == 11)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
   else if(pin == 12)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
   else if(pin == 13)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
   else if(pin == 14)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
   else if(pin == 15)  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
   
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_InitStructure.GPIO_Speed = speed;

   GPIO_Init(GPIOA, &GPIO_InitStructure);
}*/
