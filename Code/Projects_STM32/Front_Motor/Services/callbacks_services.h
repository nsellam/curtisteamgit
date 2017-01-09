/**
 * @file callbacks_services.h
 * @author Curtis Team
 * @brief Headers of callbacks functions
 */
 
#ifndef CALLBACKS_SERVICES_H
#define CALLBACKS_SERVICES_H

#include <stm32f10x.h>

/**
 * @fn callbacks_services_exti
 * @brief Produce the adequate call of sensor callback according to EXTI_Line given as argument
 * @param EXTI_Line -> uint32_t (Line whose EXTI was triggered)
*/
//void callbacks_services_exti(uint32_t EXTI_Line);

/**
 * @fn callbacks_services_speed_sensor
 * @brief Produce a call of 
 */
//void callbacks_services_hall_period (void);

/**
 * @fn callbacks_services_reset_time_to_next_hall_period
 * @brief Reinit private variable indicating time remainng before the next hall sensor period
 */
//void callbacks_services_reset_time_to_next_hall_period (void);

/**
* @fn callbacks_services_exti_front_motor
* @brief Callback service for front motor
* @param EXTI Line related to the front motor's direction 
* @return void
*/
void callbacks_services_exti_front_motor(uint32_t EXTI_Line);


#endif //CALLBACKS_SERVICES_H
