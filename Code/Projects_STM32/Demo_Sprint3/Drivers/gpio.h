#ifndef GPIO_H
#define GPIO_H

#include <stm32f10x.h>

/**
 * @fn GPIO_QuickInit
 * @brief Make the initialization of the given Pin with the parameters specified
 * @param GPIOx -> GPIO_TypeDef (port of the pin to init)
 * @param pin   -> uint16_t (# of the pin to init)
 * @param mode  -> GPIOMode_TypeDef (mode of GPIO => GPIO_Mode_AIN, GPIO_Mode_IN_FLOATING, GPIO_Mode_IPD, GPIO_Mode_IPU, GPIO_Mode_Out_OD, GPIO_Mode_Out_PP, GPIO_Mode_AF_OD, GPIO_Mode_AF_PP8)
 */
void GPIO_QuickInit(GPIO_TypeDef *GPIOx, uint16_t pin, GPIOMode_TypeDef mode);

#endif //GPIO_H
