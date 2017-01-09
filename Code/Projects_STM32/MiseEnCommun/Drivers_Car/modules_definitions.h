/**
 * @file    modules_definitions.h
 * @author  Curtis Team
 * @brief   Modules description
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MODULES_DEFINES_H
#define _MODULES_DEFINES_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
    HALLSENSOR_L,
    HALLSENSOR_R
} HallSensors_Enum;

typedef HallSensors_Enum PositionSensor_Enum;
typedef HallSensors_Enum SpeedSensor_Enum;

typedef enum {
    FRONT_MOTOR,
    REAR_MOTOR_L,
    REAR_MOTOR_R
} Motors_Enum;

/* Exported constants --------------------------------------------------------*/
/**
 * @brief       Number of hall sensors available
*/
#define HALLSENSORS_NUMBER                      2

/**
 * @brief       Identifier used to designate the hall sensor associated to the left rear motor 
*/
#define HALL_SENSOR_L_IDENTIFIER                0x00

/**
 * @brief       Identifier used to designate the hall sensor associated to the right rear motor 
*/
#define HALL_SENSOR_R_IDENTIFIER                0x01

/**
 * @brief       Number of the exti-line corresponding to the left hall sensor
*/
#define HALLSENSOR_L_LINE                      EXTI_Line8

/**
 * @brief       Number of the exti-line corresponding to the right hall sensor
*/
#define HALLSENSOR_R_LINE                      EXTI_Line9

/**
 * @brief       Number of the pin where the left hall sensor is plugged
*/
#define HALLSENSOR_L_PIN                       GPIO_Pin_8

/**
 * @brief       Number of the pin where the right hall sensor is plugged
*/
#define HALLSENSOR_R_PIN                       GPIO_Pin_9

/**
 * @brief       Pointer on the GPIO port interfacing the left hall sensor
*/
#define HALLSENSOR_L_GPIO                      GPIOC

/**
 * @brief       Pointer on the GPIO port interfacing the right hall sensor
*/
#define HALLSENSOR_R_GPIO                      GPIOC

/**
 * @brief       Number of fronts to count to get one full lap of wheel
*/ 
#define HALLSENSOR_NUMBER_OF_SECTORS            36

/**
 * @brief       Number of motors used on the car
*/ 
#define MOTORS_NUMBER                           3

/**
 * @brief       Minimum PWM value used to turn the motors backwards to their maximum
*/
#define MOTORS_PWM_MIN                          ((float)0.245)

/**
 * @brief       Maximum PWM value used to turn the motors forwards to their maximum
*/
#define MOTORS_PWM_MAX                          ((float)0.754)

/**
 * @brief       Zero PWM value used to turn the motors off
*/
#define MOTORS_PWM_ZERO                         ((float)0.500)

/**
 * @brief       Maximum variation of the PWM value from the PWM_ZERO value
*/
#define MOTORS_PWM_DELTA_MAX                    (((MOTORS_PWM_MAX - MOTORS_PWM_ZERO) < (MOTORS_PWM_ZERO - MOTORS_PWM_MIN)) ? (MOTORS_PWM_MAX - MOTORS_PWM_ZERO) : (MOTORS_PWM_ZERO - MOTORS_PWM_MIN))

/**
 * @brief       Identifier used to designate left rear motor 
*/
#define FRONT_MOTOR_IDENTIFIER                     0x00

/**
 * @brief       Identifier used to designate left rear motor 
*/
#define REAR_MOTOR_L_IDENTIFIER                     0x01

/**
 * @brief       Identifier used to designate right rear motor 
*/
#define REAR_MOTOR_R_IDENTIFIER                     0x02

/**
 * @brief       Timer used to motors PWM generation
*/
#define REAR_MOTOR_L_TIM                             TIM1

/**
 * @brief       Channel used to motors PWM generation
*/
#define REAR_MOTOR_L_TIM_CHANNEL                     TIM_Channel_1

/**
 * @brief       Period used to motors PWM generation in Hz
*/
#define MOTORS_PWM_FREQUENCY                        (20e3)

/**
 * @brief       GPIO used to enable the motor
*/
#define REAR_MOTOR_L_ENABLE_GPIO                    GPIOC

/**
 * @brief       Pin used to enable the motor
*/
#define REAR_MOTOR_L_ENABLE_PIN                     GPIO_Pin_13


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif // _MODULES_DEFINES_H
