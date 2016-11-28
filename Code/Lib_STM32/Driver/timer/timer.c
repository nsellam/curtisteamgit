#include "timer.h"

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stdint.h>
#include <stm32f10x.h>
#include <gpio.h>


/********************************/
/*         CONSTANTS            */
/********************************/

/**
* @def PSC_VALUE_MIN
* @brief Min Value of Prescaler register in STM32
*/
#define PSC_VALUE_MIN ((uint16_t)0)     // CK_CNT = 72MHz

/**
* @def PSC_VALUE_MAX
* @brief Max Value of Prescaler register in STM32
*/
#define PSC_VALUE_MAX ((uint16_t)65535) // CK_CNT ~ 1.1kHz

/**
* @def ARR_VALUE_MIN
* @brief Min Value of Autoreload register in STM32
*/
#define ARR_VALUE_MIN ((uint16_t)0)

/**
* @def ARR_VALUE_MAX
* @brief Max Value of Autoreload register in STM32
*/
#define ARR_VALUE_MAX ((uint16_t)65535)

/**
* @def SYSTEM_CORE_CLOCK
* @brief Clock value in STM32
*/
#define SYSTEM_CORE_CLOCK 72.0e6

#define PSC_CEILING_LIMIT 1.0e-6



/********************************/
/*       FUNCTIONS              */
/********************************/

//------- Private prototypes ----------
static void RCC_Config(TIM_TypeDef *Timer);

// IRQ Handlers
void (*TIM1_IT_Function)(void);
void (*TIM2_IT_Function)(void);
void (*TIM3_IT_Function)(void);
void (*TIM4_IT_Function)(void);


//------- Private functions -----------
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


void TIM1_UP_IRQHandler(void) {
   // Clear interrupt
   TIM1->SR &= ~TIM_SR_UIF;
   TIM1_IT_Function();
}

void TIM2_IRQHandler(void) {
   // Clear interrupt
   TIM2->SR &= ~TIM_SR_UIF;
   TIM2_IT_Function();
}

void TIM3_IRQHandler(void) {
   // Clear interrupt
   TIM3->SR &= ~TIM_SR_UIF;
   TIM3_IT_Function();
}

void TIM4_IRQHandler(void) {
   // Clear interrupt
   TIM4->SR &= ~TIM_SR_UIF;
   TIM4_IT_Function();
}

void TIM1_CC_IRQHandler(void) {
   // Clear interrupt
   TIM1->SR &= ~TIM_SR_UIF;
   TIM1_IT_Function();
}

void TIM2_CC_IRQHandler(void) {
   // Clear interrupt
   TIM2->SR &= ~TIM_SR_UIF;
   TIM2_IT_Function();
}

void TIM3_CC_IRQHandler(void) {
   // Clear interrupt
   TIM3->SR &= ~TIM_SR_UIF;
   TIM3_IT_Function();
}

void TIM4_CC_IRQHandler(void) {
   // Clear interrupt
   TIM4->SR &= ~TIM_SR_UIF;
   TIM4_IT_Function();
}

//------- Public functions ------------

/**
* @fn Timer_1234_Init
* @brief Initializes timers 1, 2, 3 or 4
* @param Timer Timer to be used
* @param period_us Timer period in microseconds  
* @return Period in microseconds obtained
*/
float Timer_1234_Init(TIM_TypeDef *Timer, float period_us) {
   volatile const float fclock = (float)SystemCoreClock;
   const float frequency_ratio = SYSTEM_CORE_CLOCK * period_us / US_PER_S;
   float    PSC_Val_f, ARR_Val_f;
   uint16_t PSC_Val  , ARR_Val  ;
   
   // Active la clock
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
* @fn Timer_1234_Enable
* @brief Enables timers 1, 2, 3 or 4
* @param Timer Timer to be used  
* @return void
*/
void Timer_1234_Enable(TIM_TypeDef *Timer) {
   Timer->CR1 |= TIM_CR1_CEN;
}

/**
* @fn Timer_1234_Disable
* @brief Disables timers 1, 2, 3 or 4
* @param Timer Timer to be used  
* @return void
*/
void Timer_1234_Disable(TIM_TypeDef *Timer) {
   Timer->CR1 &= ~TIM_CR1_CEN;
}

/**
* @fn Timer_1234_ITEnable
* @brief Activates Overflow timer interruption and set function and spriority 
* @param Timer Timer to be used
* @param priority Priority of interruption
* @param IT_function run in interruption handling 
* @return void
*/
void Timer_1234_ITEnable(TIM_TypeDef *Timer, uint8_t priority, void (*IT_function)(void)) {
   IRQn_Type Timer_IRQn;
   if (Timer == TIM1) {
      Timer_IRQn = TIM1_UP_IRQn;
      TIM1_IT_Function = IT_function;
   }
   else if (Timer == TIM2) {
      Timer_IRQn = TIM2_IRQn;
      TIM2_IT_Function = IT_function;
   }
   else if (Timer == TIM3) {
      Timer_IRQn = TIM3_IRQn;
      TIM3_IT_Function = IT_function;
   }
   else if (Timer == TIM4) {
      Timer_IRQn = TIM4_IRQn;
      TIM4_IT_Function = IT_function;
   }
   else return;

   // Set priority
   NVIC_SetPriority(Timer_IRQn, (uint32_t)priority);
   NVIC_EnableIRQ(Timer_IRQn);

   // UIE
   Timer->DIER |= TIM_DIER_UIE;
}

/**
* @fn Timer_1234_Get_Counter_Val
* @brief Gets timer Counter register value
* @param Timer Timer to be used  
* @return void
*/
uint16_t Timer_1234_Get_Counter_Val(TIM_TypeDef* Timer) {
   return (uint16_t)Timer->CNT;
}





/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_timer_configuration(TIM_TypeDef *timer){
  if (timer == TIM1)       RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  else if (timer == TIM2)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  else if (timer == TIM3)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  else if (timer == TIM4)  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
   
}


/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(IRQn_Type Timer_IRQn, uint8_t PreemptionPriority, uint8_t SubPriority, void (*IT_function)(void)){
  /* Enable the TIMx global Interrupt */
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = Timer_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
