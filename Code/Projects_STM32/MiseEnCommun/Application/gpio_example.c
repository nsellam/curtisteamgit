#include <stdint.h>
#include <stm32f10x.h>

#include "gpio.h"

/**
 * @brief 	Sets PC13 to '1'
 * @retval 	None
*/
void GPIO_Example(void) {
    GPIO_QuickInit(GPIOC, GPIO_Pin_13, GPIO_Mode_Out_PP);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}
