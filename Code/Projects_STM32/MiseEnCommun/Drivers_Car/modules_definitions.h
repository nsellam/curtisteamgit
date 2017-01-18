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
#include <stm32f10x.h>

/* Exported types ------------------------------------------------------------*/
typedef enum {
    HALLSENSOR_L = 0,
    HALLSENSOR_R = 1
} HallSensors_Enum;

typedef HallSensors_Enum PositionSensor_Enum;
typedef HallSensors_Enum SpeedSensor_Enum;

typedef enum {
    FRONT_MOTOR = 0,
    REAR_MOTOR_L = 1,
    REAR_MOTOR_R = 2
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
 * @brief       ADC used for motors current capture 
*/
#define MOTORS_ADC                                ADC1

/**
 * @brief       Sampling time for battery
*/
#define MOTORS_CURRENT_SAMPLING                     ADC_SampleTime_41Cycles5

/**
 * @brief       Identifier used to designate left rear motor 
*/
#define FRONT_MOTOR_IDENTIFIER                     0x00

/**
 * @brief       Identifier used to designate left rear motor 
*/
#define REAR_MOTOR_L_IDENTIFIER                     0x01

/**
 * @brief       GPIO for current capture of rear motor left
*/
#define REAR_MOTOR_L_CURRENT_GPIO                   GPIOA

/**
 * @brief       Pin for current capture of rear motor left
*/
#define REAR_MOTOR_L_CURRENT_PIN                   GPIO_Pin_4

/**
 * @brief       Rank for current capture of rear motor left
*/
#define REAR_MOTOR_L_CURRENT_RANK                   0x01

/**
 * @brief       Identifier used to designate right rear motor 
*/
#define REAR_MOTOR_R_IDENTIFIER                     0x02

/**
 * @brief       GPIO for current capture of rear motor right
*/
#define REAR_MOTOR_R_CURRENT_GPIO                   GPIOA

/**
 * @brief       Pin for current capture of rear motor right
*/
#define REAR_MOTOR_R_CURRENT_PIN                   GPIO_Pin_5

/**
 * @brief       Rank for current capture of rear motor right
*/
#define REAR_MOTOR_R_CURRENT_RANK                   0x02

/**
 * @brief       GPIO for current capture of front motor 
*/
#define FRONT_MOTOR_CURRENT_GPIO                   GPIOC

/**
 * @brief       Pin for current capture of front motor
*/
#define FRONT_MOTOR_CURRENT_PIN                   GPIO_Pin_0

/**
 * @brief       Rank for current capture of front motor 
*/
#define FRONT_MOTOR_CURRENT_RANK                   0x03

/**
 * @brief       Timer used for rear motor left PWM generation
*/
#define REAR_MOTOR_L_TIM                             TIM1

/**
 * @brief       Timer used for rear motor right PWM generation
*/
#define REAR_MOTOR_R_TIM                             TIM1

/**
 * @brief       Timer used for front motor PWM generation
*/
#define FRONT_MOTOR_TIM                              TIM1

/**
 * @brief       Channel used for rear motor left PWM generation
*/
#define REAR_MOTOR_L_TIM_CHANNEL                     TIM_Channel_1

/**
 * @brief       Channel used for rear motor right PWM generation
*/
#define REAR_MOTOR_R_TIM_CHANNEL                     TIM_Channel_2

/**
 * @brief       Channel used for front motor PWM generation
*/
#define FRONT_MOTOR_TIM_CHANNEL                      TIM_Channel_3

/**
 * @brief       Period used to motors PWM generation in Hz
*/
#define MOTORS_PWM_FREQUENCY                        (20e3)

/**
 * @brief       GPIO used to enable the rear motor left
*/
#define REAR_MOTOR_L_ENABLE_GPIO                    GPIOC

/**
 * @brief       GPIO used to enable the rear motor right
*/
#define REAR_MOTOR_R_ENABLE_GPIO                    GPIOC

/**
 * @brief       GPIO used to enable the front left
*/
#define FRONT_MOTOR_ENABLE_GPIO                     GPIOB

/**
 * @brief       Pin used to enable the rear motor left
*/
#define REAR_MOTOR_L_ENABLE_PIN                     GPIO_Pin_13

/**
 * @brief       Pin used to enable the rear motor right
*/
#define REAR_MOTOR_R_ENABLE_PIN                     GPIO_Pin_11

/**
 * @brief       Pin used to enable the front motor
*/
#define FRONT_MOTOR_ENABLE_PIN                      GPIO_Pin_2

/**
 * @brief   GPIO of the front motor's left direction sensor
 */
#define HARD_STOP_GPIO_LEFT                         GPIOC

/**
 * @brief   GPIO of the front motor's right direction sensor
 */
#define HARD_STOP_GPIO_RIGHT                        GPIOC

/**
 * @brief   GPIO pin of the front motor's left direction sensor
 */
#define HARD_STOP_PIN_LEFT                          GPIO_Pin_10

/**
 * @brief   GPIO pin of the front motor's right direction sensor
 */
#define HARD_STOP_PIN_RIGHT                         GPIO_Pin_11

/**
 * @brief   EXTI_line of the front motor's left direction sensor
 */
#define FRONT_LINE_LEFT                             EXTI_Line10

/**
 * @brief   EXTI_line of the front motor's right direction sensor
*/
#define FRONT_LINE_RIGHT                            EXTI_Line11

/**
 * @brief   EXTI_line rising signal
 */
#define HARD_STOP_TRIGGATION                        EXTI_Trigger_Falling

/**
 * @brief   Set the priority for the Exti of front_motor
 */
#define HARD_STOP_PRIORITY                          3

/**
 * @brief       Maximum current for the motors (mA)
*/
#define MAX_CURRENT                                 ((float)4000.0)
    
/**
 * @brief       GPIO of the battery
*/
#define BATTERY_GPIO                                GPIOA

/**
 * @brief       Pin of the battery
*/
#define BATTERY_PIN                                GPIO_Pin_0

/**
 * @brief       ADC used for battery
*/
#define BATTERY_ADC                                 ADC1

/**
 * @brief       Sampling time for battery
*/
#define BATTERY_SAMPLING                            ADC_SampleTime_41Cycles5

/**
 * @brief       Sampling time for battery
*/
#define BATTERY_RANK                                0x01

/**
 * @brief       ADC scale for calculating the battery level value : 4069/3.3 *(3.2 - 1.6) = 1973 = 0x07B5
*/
#define BATTERY_ADC_SCALE                           ((uint16_t)0x07B5) //1973

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif // _MODULES_DEFINES_H
