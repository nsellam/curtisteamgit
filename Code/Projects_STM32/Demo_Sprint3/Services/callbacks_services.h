#ifndef CALLBACKS_SERVICES_H
#define CALLBACKS_SERVICES_H

#include <stm32f10x.h>

/**
 * @fn callbacks_services_exti
 * @brief Produce the adequate call of sensor callback according to EXTI_Line given as argument
 * @param EXTI_Line -> uint32_t (Line whose EXTI was triggered)
*/
void callbacks_services_exti(uint32_t EXTI_Line);

#endif //CALLBACKS_SERVICES_H
