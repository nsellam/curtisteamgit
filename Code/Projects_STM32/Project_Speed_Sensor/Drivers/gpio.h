#ifndef GPIO_H
#define GPIO_H

#include <stm32f10x_gpio.h>

/**
 * @fn gpio_init
 * @brief Make the initialization of the given Pin with the parameters specified
 * @param GPIO -> GPIO_TypeDef (port of the pin to init)
 * @param Pin -> uint16_t (# of the pin to init)
 * @param GPIO_Speed -> GPIOSpeed_TypeDef (speed of GPIO => possible values are : GPIO_Speed_10MHz, GPIO_Speed_2MHz, GPIO_Speed_50MHz)
 * @param GPIO_Mode -> GPIOMode_TypeDef (mode of GPIO => GPIO_Mode_AIN, GPIO_Mode_IN_FLOATING, GPIO_Mode_IPD, GPIO_Mode_IPU, GPIO_Mode_Out_OD, GPIO_Mode_Out_PP, GPIO_Mode_AF_OD, GPIO_Mode_AF_PP8)
 */
void gpio_init (GPIO_TypeDef *GPIO, uint16_t Pin, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode);

#endif //GPIO_H
