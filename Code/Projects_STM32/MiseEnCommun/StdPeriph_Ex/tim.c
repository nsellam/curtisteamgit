/**
 * @file 	tim.c
 * @author 	Curtis Team
 * @brief 	Functions to handle Timers  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
* @brief 	Max Value of Prescaler register in STM32
*/
#define PSC_VALUE_MAX ((uint16_t)UINT16_MAX) // CK_CNT ~ 1.1kHz

/**
* @brief 	Max Value of Autoreload register in STM32
*/
#define ARR_VALUE_MAX ((uint16_t)UINT16_MAX)

/**
* @brief    Prescaler ceiling limit
*/
#define PSC_CEILING_LIMIT 1.0e-6

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RCC_timer_configuration(TIM_TypeDef *timer);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief 	Makes the initialization of the given Analog to Digital Converter (ADC) with the parameters specified
*/
void TIM_QuickInit(TIM_TypeDef *timer, float period_us) {
   volatile const float fclock = (float)SystemCoreClock;
   const float frequency_ratio = fclock * period_us / US_PER_S;
   float    PSC_val_f, ARR_val_f;
   uint16_t PSC_val  , ARR_val;
   volatile float aux;
   
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   
   // Active la clock
   RCC_timer_configuration(timer);

   // PSC conf
   PSC_val_f = frequency_ratio / ((float)ARR_VALUE_MAX + 1.0) - 1.0;
   PSC_val = (uint16_t)PSC_val_f;                                    // floor
   if((PSC_val_f - (float)PSC_val) > PSC_CEILING_LIMIT) PSC_val++;   // ceiling
   if(PSC_val_f > PSC_VALUE_MAX) PSC_val = PSC_VALUE_MAX;            // saturation
  
   // ARR conf
   ARR_val_f = frequency_ratio / ((float)PSC_val + 1.0) - 1.0;
   ARR_val = (uint16_t)ARR_val_f;                           // floor
   if(ARR_val_f > ARR_VALUE_MAX) ARR_val = ARR_VALUE_MAX;   // saturation
   
  /* set everything back to default values */
  TIM_TimeBaseStructInit (&TIM_TimeBaseStructure);
  /* only changes from the defaults are needed */
  TIM_TimeBaseStructure.TIM_Period = ARR_val;
  TIM_TimeBaseStructure.TIM_Prescaler = PSC_val;
  TIM_TimeBaseInit (timer, &TIM_TimeBaseStructure);
}

/**
 * @brief   Enables timers 1, 2, 3 or 4
 * @param   Timer Timer to be used  
 * @return  void
*/
void TIM_start (TIM_TypeDef *timer){
  TIM_Cmd (timer, ENABLE);
}
 
/**
 * @brief   Disables timers 1, 2, 3 or 4
 * @param   Timer Timer to be used  
 * @retval  None
*/
void TIM_disable (TIM_TypeDef *timer){
  TIM_Cmd (timer, DISABLE);
}

__weak void TIM_Callback(TIM_TypeDef TIMx) {}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Configures the different system clocks.
 * @param   None
 * @retval  None
*/
void RCC_timer_configuration(TIM_TypeDef *timer) {
       if (timer == TIM1)  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  else if (timer == TIM2)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  else if (timer == TIM3)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  else if (timer == TIM4)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
}

void TIM_ITHandler(TIM_TypeDef TIMx) {
    TIM_Callback(TIMx);
}
