/**
 * @file    motors.c
 * @author  Curtis Team
 * @brief   Functions to handle motors  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "motors.h"
#include "gpio.h"
#include "tim.h"
#include "pwm.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
direction_TypeDef Motors_Direction[MOTORS_NUMBER] = {NEUTRAL, NEUTRAL, NEUTRAL};

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief       Initializes specified motor.
 * @param       Motor Motor to be considered.
 * @retval      None
*/
void Motor_QuickInit(Motors_Enum Motor) {
    
    TIM_TypeDef *TIMx;
    uint16_t Channelx;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
    uint8_t Motor_Identifier;
    
    if (Motor == REAR_MOTOR_L) {
        TIMx = REAR_MOTOR_L_TIM;
        Channelx = REAR_MOTOR_L_TIM_CHANNEL;
        GPIOx = REAR_MOTOR_L_ENABLE_GPIO;
        GPIO_Pin = REAR_MOTOR_L_ENABLE_PIN;
        Motor_Identifier = REAR_MOTOR_L_IDENTIFIER;
        TIM_Remap(TIMx, PartialRemap1);
    }
    else if (Motor == REAR_MOTOR_R) {
        TIMx = REAR_MOTOR_R_TIM;
        Channelx = REAR_MOTOR_R_TIM_CHANNEL;
        GPIOx = REAR_MOTOR_R_ENABLE_GPIO;
        GPIO_Pin = REAR_MOTOR_R_ENABLE_PIN;
        Motor_Identifier = REAR_MOTOR_R_IDENTIFIER;
        TIM_Remap(TIMx, PartialRemap1);
    }
    else if (Motor == FRONT_MOTOR) {
        TIMx = FRONT_MOTOR_TIM;
        Channelx = FRONT_MOTOR_TIM_CHANNEL;
        GPIOx = FRONT_MOTOR_ENABLE_GPIO;
        GPIO_Pin = FRONT_MOTOR_ENABLE_PIN;
        Motor_Identifier = FRONT_MOTOR_IDENTIFIER; 
        TIM_Remap(TIMx, PartialRemap1);
    }
    else return;
    
    PWM_QuickInit(TIMx, Channelx, MOTORS_PWM_FREQUENCY);
    PWM_QuickInit_Complementary(TIMx, Channelx);
    PWM_SetDutyCycle(TIMx, Channelx, MOTORS_PWM_ZERO);
    GPIO_QuickInit(GPIOx, GPIO_Pin, GPIO_Mode_Out_PP);
    PWM_Start(TIMx);
    
    Motors_Direction[Motor_Identifier] = NEUTRAL;
}

/**
 * @brief   Sets speed on the indicated motor. 
 * @param   Motor Motor to be considered.
 * @param   speed Expecteed speed on the motor. 
 * @retval  None
*/
void Motor_setSpeed(Motors_Enum Motor, float speed) {
    float duty_cycle;
    TIM_TypeDef *TIMx;
    uint8_t Motor_Identifier;
    uint16_t Channelx;
    
    if (Motor == REAR_MOTOR_L) {
        TIMx = REAR_MOTOR_L_TIM;
        Channelx = REAR_MOTOR_L_TIM_CHANNEL;
        Motor_Identifier = REAR_MOTOR_L_IDENTIFIER;        
    }
    else if (Motor == REAR_MOTOR_R) {
        TIMx = REAR_MOTOR_R_TIM;
        Channelx = REAR_MOTOR_R_TIM_CHANNEL;
        Motor_Identifier = REAR_MOTOR_R_IDENTIFIER;        
    }
    else if (Motor == FRONT_MOTOR) {
        TIMx = FRONT_MOTOR_TIM;
        Channelx = FRONT_MOTOR_TIM_CHANNEL;
        Motor_Identifier = FRONT_MOTOR_IDENTIFIER; 
    }
    else return;
    
            if(speed >  MOTORS_SPEED_MAX) speed =  MOTORS_SPEED_MAX;
    else    if(speed < -MOTORS_SPEED_MAX) speed = -MOTORS_SPEED_MAX;

    duty_cycle = (MOTORS_PWM_DELTA_MAX)/(MOTORS_SPEED_DELTA) * speed + MOTORS_PWM_ZERO;
    
            if (duty_cycle == MOTORS_PWM_ZERO) Motors_Direction[Motor_Identifier] = NEUTRAL;
    else    if (duty_cycle >  MOTORS_PWM_ZERO) Motors_Direction[Motor_Identifier] = FORWARD;
    else    if (duty_cycle <  MOTORS_PWM_ZERO) Motors_Direction[Motor_Identifier] = BACKWARD;
    
    PWM_SetDutyCycle(TIMx, Channelx, duty_cycle);
}

void Motor_Disable(Motors_Enum Motor);

/**
 * @brief   Allows motor activation
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void Motor_Enable(Motors_Enum Motor) {
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
    
    if (Motor == REAR_MOTOR_L) {
        GPIOx = REAR_MOTOR_L_ENABLE_GPIO;
        GPIO_Pin = REAR_MOTOR_L_ENABLE_PIN;
    }
    else if (Motor == REAR_MOTOR_R) {
        GPIOx = REAR_MOTOR_R_ENABLE_GPIO;
        GPIO_Pin = REAR_MOTOR_R_ENABLE_PIN;
    }
    else if (Motor == FRONT_MOTOR) {
        GPIOx = FRONT_MOTOR_ENABLE_GPIO;
        GPIO_Pin = FRONT_MOTOR_ENABLE_PIN;
    }
    else return;
    
    GPIO_SetBits(GPIOx, GPIO_Pin);
}

/**
 * @brief   Forbids motor activation.
 * @param   Motor Motor to be considered.
 * @retval  None
*/
void Motor_Disable(Motors_Enum Motor) {
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
    
    if (Motor == REAR_MOTOR_L) {
        GPIOx = REAR_MOTOR_L_ENABLE_GPIO;
        GPIO_Pin = REAR_MOTOR_L_ENABLE_PIN;
    }
    else if (Motor == REAR_MOTOR_R) {
        GPIOx = REAR_MOTOR_R_ENABLE_GPIO;
        GPIO_Pin = REAR_MOTOR_R_ENABLE_PIN;
    }
    else if (Motor == FRONT_MOTOR) {
        GPIOx = FRONT_MOTOR_ENABLE_GPIO;
        GPIO_Pin = FRONT_MOTOR_ENABLE_PIN;
    }
    else return;
    
    GPIO_ResetBits(GPIOx, GPIO_Pin);
}

/**
 * @brief   Returns current in specified motor.
 * @param   Motor Motor to be considered.
 * @retval  Value of current
*/
int16_t Motor_getCurrent(Motors_Enum Motor) {
    return (int16_t) 0x00;
}
/* Private functions ---------------------------------------------------------*/

