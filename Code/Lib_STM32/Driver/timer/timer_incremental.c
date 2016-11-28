#include "timer_incremental.h"

#include <stdint.h>
#include <stm32f10x.h>

#include <timer.h>

#define TIMx TIM3
#define IRQ_PRIORITY 1

int nb_interrupt = 0;

void Timer_Inc_Init(TIM_TypeDef *Timer) {
   Timer->CCMR1 &= ~TIM_CCMR1_CC1S;    // permet de lier TI1FP1 à TI1
   Timer->CCMR1 |= TIM_CCMR1_CC1S_0;   // permet de lier TI1FP1 à TI1
   Timer->CCMR2 &= ~TIM_CCMR2_CC3S;    // permet de lier TI2FP2 à TI2
   Timer->CCMR2 |= TIM_CCMR2_CC3S_0;   // permet de lier TI2FP2à TI2
   Timer->CCER &=~ TIM_CCER_CC1P;      // TI1FP1 non-inverted, TI1FP1 = TI1
   Timer->CCER &=~ TIM_CCER_CC2P;      // TI2FP2 non-inverted, TI2FP2 = TI2
   Timer->SMCR &= ~TIM_SMCR_SMS;
   Timer->SMCR |= TIM_SMCR_SMS_1;      // counter counts up/down on TI1FP1 edge depending on TI2FP2 level
   Timer->ARR = ARR_VALUE_MAX;
   Timer->PSC &= ~TIM_PSC_PSC;
   Timer->CNT &= ~TIM_CNT_CNT;         // mettre le compteur à 0

   //interruption pour l'index
   EXTI->IMR |= (1 << 5);              // Autorisation de l'interruption de la ligne 5, correspondant à la broche « PA5 »
   EXTI->RTSR |= (1 << 5);             // Activation du déclenchement de l'interruption sur un front montant de la broche « PA5 »
   AFIO->EXTICR[2] &=~ (0x000000F0);   // L'interruption « EXTI5 » doit être provoquée par une modification d'état de la broche « PA5 »
   NVIC_EnableIRQ(EXTI9_5_IRQn);       // Autorisation de l'interruption « EXTI9_5 »
   NVIC_SetPriority(EXTI9_5_IRQn, IRQ_PRIORITY);
}

int Get_Nb_Interrupt(void) {
   return nb_interrupt;
}

void Set_Nb_Interrupt(int n) {
   nb_interrupt = n;
}

void EXTI9_5_IRQHandler(void) {
   int16_t counter = TIMx->CNT;
   uint16_t reload = TIMx->ARR;
   
   if(nb_interrupt == 0)
      nb_interrupt++;
   else if(nb_interrupt == 1) {
      TIMx->ARR = TIMx->CNT;
      nb_interrupt++;
   }

   EXTI->PR |= (1 << 5);               // Réarmement de l'interruption « EXTI5 »
   TIMx->CNT &= ~TIM_CNT_CNT;
}
