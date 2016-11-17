
/* -------------------------------------------------------------------------- */
/* ----------------------------- Includes ----------------------------------- */
/* -------------------------------------------------------------------------- */
#include "switch.h"

#include <stdint.h>
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define GPIO_SW                        GPIOC
#define RCC_APBxPeriphClockCmd_GPIO_SW RCC_APB2PeriphClockCmd
#define RCC_APBxPeriph_GPIO_SW         RCC_APB2Periph_GPIOC
#define GPIO_Pin_SW                    GPIO_Pin_13

/* -------------------------------------------------------------------------- */
/* ------------------------ Private prototypes ------------------------------ */
/* -------------------------------------------------------------------------- */

static void RCC_Configuration(void);
static void GPIO_Configuration(void);

/* -------------------------------------------------------------------------- */
/* ------------------------- Public functions ------------------------------- */
/* -------------------------------------------------------------------------- */

void Switch_Config(void) {
   // System clocks configuration
   RCC_Configuration();

   // Configure the GPIO port
   GPIO_Configuration();
}


uint8_t Switch_IsPressed(void) {
   return !GPIO_ReadInputDataBit(GPIO_SW, GPIO_Pin_SW);
}

/* -------------------------------------------------------------------------- */
/* ------------------------- Private functions ------------------------------ */
/* -------------------------------------------------------------------------- */

void RCC_Configuration(void) {
   // GPIO_SW clock enable
   RCC_APBxPeriphClockCmd_GPIO_SW(RCC_APBxPeriph_GPIO_SW, ENABLE);
}

void GPIO_Configuration(void) {
   GPIO_InitTypeDef GPIO_InitStructure;

   // GPIO_Pin_SW configuration
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_SW;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

   GPIO_Init(GPIO_SW, &GPIO_InitStructure);
}
