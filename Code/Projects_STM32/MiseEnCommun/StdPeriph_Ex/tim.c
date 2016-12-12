/**
 * @file 		tim.c
 * @author 	Curtis Team
 * @brief 	Functions to handle Timers  
 */
 
/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>
#include <stdint.h>
#include "tim.h"
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
* @brief 	Min Value of Prescaler register in STM32
*/
#define PSC_VALUE_MIN ((uint16_t)0)     // CK_CNT = 72MHz

/**
* @brief 	Max Value of Prescaler register in STM32
*/
#define PSC_VALUE_MAX ((uint16_t)UINT16_MAX) // CK_CNT ~ 1.1kHz

/**
* @brief 	Min Value of Autoreload register in STM32
*/
#define ARR_VALUE_MIN ((uint16_t)0)

/**
* @brief 	Max Value of Autoreload register in STM32
*/
#define ARR_VALUE_MAX ((uint16_t)UINT16_MAX)

/**
* @brief 	Clock value in STM32
*/
#define SYSTEM_CORE_CLOCK 72.0e6

/**
* @brief 	Prescaler ceiling limit
*/
#define PSC_CEILING_LIMIT 1.0e-6

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void RCC_Config(TIM_TypeDef *Timer);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief 	Makes the initialization of the given Analog to Digital Converter (ADC) with the parameters specified
 * @param 	Timer Timer to be used
 * @param 	period_us Timer period in microseconds  
 * @return 	Period in microseconds obtained
*/
float TIM_QuickInit(TIM_TypeDef *Timer, float period_us) {
   volatile const float fclock = (float)SystemCoreClock;
   const float frequency_ratio = SYSTEM_CORE_CLOCK * period_us / US_PER_S;
   float    PSC_Val_f, ARR_Val_f;
   uint16_t PSC_Val  , ARR_Val  ;
   
   // Active the clock
   RCC_Config(Timer);

   // PSC conf
   PSC_Val_f = frequency_ratio / ((float)ARR_VALUE_MAX + 1.0) - 1.0;
   PSC_Val = (uint16_t)PSC_Val_f;                                    // floor
   if((PSC_Val_f - (float)PSC_Val) > PSC_CEILING_LIMIT) PSC_Val++;   // ceiling
   if(PSC_Val_f > PSC_VALUE_MAX) PSC_Val = PSC_VALUE_MAX;            // saturation
   Timer->PSC = PSC_Val;

   // ARR conf
   ARR_Val_f = frequency_ratio / ((float)PSC_Val + 1.0) - 1.0;
   ARR_Val = (uint16_t)ARR_Val_f;                           // floor
   if(ARR_Val_f > ARR_VALUE_MAX) ARR_Val = ARR_VALUE_MAX;   // saturation
   Timer->ARR = ARR_Val;

   return ((float)PSC_Val + 1.0) * ((float)ARR_Val + 1.0) * US_PER_S / SYSTEM_CORE_CLOCK;
}

/**
 * @brief 		Enables specified timer
 * @param 		Timer Timer to be used  
 * @return 	none
*/
void Timer_1234_Enable(TIM_TypeDef *Timer) {
   Timer->CR1 |= TIM_CR1_CEN;
}

/**
* @brief 		Disables specified timer
* @param 		Timer Timer to be used  
* @return 	none
*/
void Timer_1234_Disable(TIM_TypeDef *Timer) {
   Timer->CR1 &= ~TIM_CR1_CEN;
}

/**
 * @brief 	Callback associated to TIM interrupts 
*/
void TIM_Callback(void) {
	// A VOIR CE QU'ON MET ICI...
}

/* Private functions ---------------------------------------------------------*/
void RCC_Config(TIM_TypeDef *Timer) {
   if (Timer == TIM1)
      RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
   else if (Timer == TIM2)
      RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
   else if (Timer == TIM3)
      RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
   else if (Timer == TIM4)
      RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
}
