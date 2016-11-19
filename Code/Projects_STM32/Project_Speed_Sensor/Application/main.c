#include <stdint.h>
#include "stm32f10x.h"

// a mettre dans .h
#define EXTI_ERROR_INVALID_LINE					-1
#define EXTI_ERROR_INVALID_CHANNEL			-2

// a laisser dans .c
#define ERROR_LINE_UNREACHABLE	0xFFFFFFFF
#define ERROR_COMPUTING_CHANNEL	0xFF

uint32_t Pin_to_EXTI_Line (uint16_t Pin);
uint8_t Line_to_IRQn (uint32_t Line);


/**
 * @fn 
 * @brief 
 * @param 
 * @return 
 * @value 
*/
int Init_EXTI (GPIO_TypeDef GPIO, uint16_t Pin , EXTIMode_TypeDef EXTI_Mode, EXTITrigger_TypeDef EXTITrigger, uint8_t Priority, uint8_t SubPriority) {

	uint16_t error_code = 0;
	
	GPIO_InitTypeDef* GPIO_InitStruct; 
	EXTI_InitTypeDef* EXTI_InitStruct;
	NVIC_InitTypeDef* NVIC_InitStruct;
	
	uint32_t Line_Number = Pin_to_EXTI_Line(Pin); 
	uint8_t IRQChannel = Line_to_IRQn (Line_Number);
	
	if (Line_Number == ERROR_LINE_UNREACHABLE) return EXTI_ERROR_INVALID_LINE; else {}
	if (IRQChannel == ERROR_COMPUTING_CHANNEL) return EXTI_ERROR_INVALID_CHANNEL; else {}
			
	// Configure Port Pin as input and set GPIO speed to HIGH
	GPIO_InitStruct->GPIO_Pin = Pin;
	GPIO_InitStruct->GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AIN;
	
	GPIO_Init(&GPIO, GPIO_InitStruct);

	// CLOCKS ????????
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


	// Ensure SYSCFFG clock enable 
	// TODO §§§§§§§§

	// Connect EXTI Line to port pin 
	// TODO §§§§§§§§

	// Configure the particular EXTI 
	EXTI_InitStruct->EXTI_Line = Line_Number;
	EXTI_InitStruct->EXTI_Mode = EXTI_Mode;
	EXTI_InitStruct->EXTI_Trigger = EXTITrigger;
	EXTI_InitStruct->EXTI_LineCmd = ENABLE;
	
	EXTI_Init(EXTI_InitStruct);

	// Add IRQ Vector to NVIC
	NVIC_InitStruct->NVIC_IRQChannel = IRQChannel; 
	NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority = Priority; 
	NVIC_InitStruct->NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStruct->NVIC_IRQChannelCmd = ENABLE; 
	
	NVIC_Init(NVIC_InitStruct);
					
	
	return error_code; 
}

/**
 * @fn Pin_to_EXTI_Line
 * @brief Return EXTI_Line associated to Pin number passed in argument
 * @param Pin -> uint16_t (Pin number with numerotation given by GPIO_Pin_X)
 * @return uint32_t (EXTI_Line corresponding to Pin passed as argument)
 * @retval EXTI_Line0 to EXTI_Line15 if Pin is valid, ERROR_LINE_UNREACHABLE if not
*/
uint32_t Pin_to_EXTI_Line (uint16_t Pin) {
	uint32_t Line = ERROR_LINE_UNREACHABLE; 
	
	switch (Pin) {
		case (GPIO_Pin_0) : 
			Line = EXTI_Line0;
			break;
		case (GPIO_Pin_1) : 
			Line = EXTI_Line1;
			break;
		case (GPIO_Pin_2) : 
			Line = EXTI_Line2;
			break;
		case (GPIO_Pin_3) : 
			Line = EXTI_Line3;
			break;
		case (GPIO_Pin_4) : 
			Line = EXTI_Line4;
			break;
		case (GPIO_Pin_5) : 
			Line = EXTI_Line5;
			break;
		case (GPIO_Pin_6) : 
			Line = EXTI_Line6;
			break;
		case (GPIO_Pin_7) : 
			Line = EXTI_Line7;
			break;
		case (GPIO_Pin_8) : 
			Line = EXTI_Line8;
			break;
		case (GPIO_Pin_9) : 
			Line = EXTI_Line9;
			break;
		case (GPIO_Pin_10) : 
			Line = EXTI_Line10;
			break;
		case (GPIO_Pin_11) : 
			Line = EXTI_Line11;
			break;
		case (GPIO_Pin_12) : 
			Line = EXTI_Line12;
			break;
		case (GPIO_Pin_13) : 
			Line = EXTI_Line13;
			break;
		case (GPIO_Pin_14) : 
			Line = EXTI_Line14;
			break;	
		case (GPIO_Pin_15) : 
			Line = EXTI_Line15;
			break;
		default :
			Line = ERROR_LINE_UNREACHABLE;
			break;
	}
	
	return Line;
}

/**
 * @fn Line_to_IRQn
 * @brief Return IRQn associated to Line number passed in argument
 * @param Line -> uint32_t (Line number with numerotation from EXTI_Line_0 to EXTI_Line_15)
 * @return uint8_t (IRQn corresponding to Line passed as argument)
 * @retval EXTI0_IRQn to EXTI15_10_IRQn if Line is valid, ERROR_COMPUTING_CHANNEL if not
*/
uint8_t Line_to_IRQn (uint32_t Line) {
	uint8_t IRQn = ERROR_COMPUTING_CHANNEL;
	if (Line == 0) {
		IRQn = EXTI0_IRQn;
	}
	else if (Line == 1) {
		IRQn = EXTI1_IRQn;
	}
	else if (Line == 2) { 
		IRQn = EXTI2_IRQn;
	}
	else if (Line == 3) { 
		IRQn = EXTI3_IRQn;
	}
	else if (Line == 4) {
		IRQn = EXTI4_IRQn;
	}	
	else if (Line > 4 && Line <= 9) {
		IRQn = EXTI9_5_IRQn;
	}	
	else if (Line > 9 && Line <= 15) {
		IRQn = EXTI15_10_IRQn;
	}	
	else {
		IRQn = ERROR_COMPUTING_CHANNEL;
	}
		
	return IRQn;
}

int main(void) {
	
	// objectif activer EXTI pour A0 
	
	
  return 0;
}

void EXTI0_IRQHandler (void)
{
	EXTI_ClearFlag(EXTI_Line0);
}

void EXTI1_IRQHandler (void)
{
	EXTI_ClearFlag(EXTI_Line1);
}

void EXTI2_IRQHandler (void)
{
	EXTI_ClearFlag(EXTI_Line2);
}

void EXTI3_IRQHandler (void)
{
	EXTI_ClearFlag(EXTI_Line3);
}

void EXTI4_IRQHandler (void)
{
	EXTI_ClearFlag(EXTI_Line4);
}