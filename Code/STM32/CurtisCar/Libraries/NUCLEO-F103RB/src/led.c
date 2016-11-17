
/* -------------------------------------------------------------------------- */
/* ----------------------------- Includes ----------------------------------- */
/* -------------------------------------------------------------------------- */
#include "led.h"

#include <stdint.h>
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define GPIO_LED                          GPIOA
#define RCC_APBxPeriphClockCmd_GPIO_LED   RCC_APB2PeriphClockCmd
#define RCC_APBxPeriph_GPIO_LED           RCC_APB2Periph_GPIOA
#define GPIO_Pin_LED                      GPIO_Pin_5

/* -------------------------------------------------------------------------- */
/* ------------------------ Private prototypes ------------------------------ */
/* -------------------------------------------------------------------------- */

static void RCC_Configuration(void);
static void GPIO_Configuration(void);

/* -------------------------------------------------------------------------- */
/* ------------------------- Public functions ------------------------------- */
/* -------------------------------------------------------------------------- */

void LED_Config(void) {
   // System clocks configuration
   RCC_Configuration();

   // Configure the GPIO port
   GPIO_Configuration();
}

void LED_On(void) {
   GPIO_SetBits(GPIO_LED, GPIO_Pin_LED);
}

void LED_Off(void) {
   GPIO_ResetBits(GPIO_LED, GPIO_Pin_LED);
}

void LED_Toggle(void) {
   GPIO_Write(GPIO_LED, GPIO_ReadOutputData(GPIO_LED) ^ (GPIO_Pin_LED));
}

void LED_Write(uint8_t val) {
   GPIO_WriteBit(GPIO_LED, GPIO_Pin_LED, (val > 0) ? Bit_SET : Bit_RESET);
}

/* -------------------------------------------------------------------------- */
/* ------------------------- Private functions ------------------------------ */
/* -------------------------------------------------------------------------- */

void RCC_Configuration(void) {
   // GPIO_LED clock enable
   RCC_APBxPeriphClockCmd_GPIO_LED(RCC_APBxPeriph_GPIO_LED, ENABLE);
}

void GPIO_Configuration(void) {
   GPIO_InitTypeDef GPIO_InitStructure;

   // GPIO_Pin_LED configuration
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_LED;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

   GPIO_Init(GPIO_LED, &GPIO_InitStructure);
}
