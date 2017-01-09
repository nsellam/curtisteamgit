/**
 * @file callbacks_services.c
 * @author Curtis Team
 * @brief Callbacks functions
 */

#include "callbacks_services.h"
#include "systick.h"
#include "front_motor.h"
#include "motor.h"

/**
* @fn callbacks_services_exti_front_motor
* @brief Callback service for front motor
* @param EXTI Line related to the front motor's direction 
* @return void
*/
void callbacks_services_exti_front_motor(uint32_t EXTI_Line) {
   
	if (EXTI_Line == FRONT_LINE_LEFT) {
		front_motor_Callback(LEFT);     
	}
    else if (EXTI_Line == FRONT_LINE_RIGHT) {
        front_motor_Callback(RIGHT);
	}
}

