/**
 * @file    gpio_example.c
 * @author  Curtis Team
 * @brief   GPIO API use case example
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief 	Sets PC13 to '1'
 * @retval 	None
*/
void GPIO_Example(void) {
    GPIO_QuickInit(GPIOC, GPIO_Pin_13, GPIO_Mode_Out_PP);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

/* Private functions ---------------------------------------------------------*/
