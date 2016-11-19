#include <stdint.h>
#include "stm32f10x.h"

#define EXTI_Line_0 		0
#define EXTI_Line_1 		1
#define EXTI_Line_2 		2
#define EXTI_Line_3 		3
#define EXTI_Line_4 		4
#define EXTI_Line_5 		5
#define EXTI_Line_6 		6
#define EXTI_Line_7 		7
#define EXTI_Line_8 		8
#define EXTI_Line_9 		9
#define EXTI_Line_10 		10
#define EXTI_Line_11 		11
#define EXTI_Line_12 		12
#define EXTI_Line_13 		13
#define EXTI_Line_14 		14
#define EXTI_Line_15 		15
#define EXTI_Line_ERROR	0xFFFFFFFF //-1 

#define PRIORITY_MIN				0
#define PRIORITY_MAX				15
#define SUB_PRIORITY_MIN		0
#define SUB_PRIORITY_MAX		15


uint32_t Pin_to_EXTI_Line (uint16_t Pin);
uint8_t Line_to_IRQn (uint32_t Line);


/**
 * @fn 
 * @brief 
 * @param 
 * @return 
 * @value 
*/
uint16_t Init_EXTI (GPIO_TypeDef GPIO, uint16_t Pin , EXTIMode_TypeDef EXTI_Mode, EXTITrigger_TypeDef EXTITrigger, uint8_t Priority, uint8_t SubPriority) {

	uint16_t error_code = 0;
	
	EXTI_InitTypeDef* EXTI_InitStruct;
	NVIC_InitTypeDef* NVIC_InitStruct;
	
	uint32_t Line_Number = Pin_to_EXTI_Line(Pin); 
	uint8_t IRQChannel = Line_to_IRQn (Line_Number);
	
	if (Line_Number != EXTI_Line_ERROR) {	
		if (IRQChannel != 0xFF) {
			if ((Priority >= PRIORITY_MIN) && (Priority <= PRIORITY_MAX)) {
				if ((SubPriority >= SUB_PRIORITY_MIN) && (SubPriority <= SUB_PRIORITY_MAX)) {
					
						// Configure Port Pin as input and set GPIO speed to HIGH
						GPIO_InitTypeDef* GPIO_InitStruct; 
						GPIO_InitStruct->GPIO_Pin = Pin;
						GPIO_InitStruct->GPIO_Speed = GPIO_Speed_50MHz;
						GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AIN;
						
						GPIO_Init(&GPIO, GPIO_InitStruct);
					
						// CLOCKS ????????
							
						// Ensure SYSCFFG clock enable 
						
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
										
				}
				else {
					error_code = 4; // invalid Priority
				}
			}
			else {
				error_code = 3; // invalid SubPriority
			}
		}
		else {
			error_code = 2; // invalid IRQChannel (due to bad Line_Number)
		}
	}
	else { 
		error_code = 1; // invalid Line_Number
	}
	
	return error_code; 
}

/**
 * @fn Pin_to_EXTI_Line
 * @brief Return EXTI_Line associated to Pin number passed in argument
 * @param Pin -> uint16_t (Pin number with numerotation given by GPIO_Pin_X)
 * @return uint32_t (EXTI_Line corresponding to Pin passed as argument)
 * @value EXTI_Line_0 to EXTI_Line_15 if Pin is valid, EXTI_Line_ERROR (0xFFFFFFFF) if not
*/
uint32_t Pin_to_EXTI_Line (uint16_t Pin) {
	uint32_t Line = EXTI_Line_ERROR; 
	
	switch (Pin) {
		case (GPIO_Pin_0) : 
			Line = EXTI_Line_0;
			break;
		case (GPIO_Pin_1) : 
			Line = EXTI_Line_1;
			break;
		case (GPIO_Pin_2) : 
			Line = EXTI_Line_2;
			break;
		case (GPIO_Pin_3) : 
			Line = EXTI_Line_3;
			break;
		case (GPIO_Pin_4) : 
			Line = EXTI_Line_4;
			break;
		case (GPIO_Pin_5) : 
			Line = EXTI_Line_5;
			break;
		case (GPIO_Pin_6) : 
			Line = EXTI_Line_6;
			break;
		case (GPIO_Pin_7) : 
			Line = EXTI_Line_7;
			break;
		case (GPIO_Pin_8) : 
			Line = EXTI_Line_8;
			break;
		case (GPIO_Pin_9) : 
			Line = EXTI_Line_9;
			break;
		case (GPIO_Pin_10) : 
			Line = EXTI_Line_10;
			break;
		case (GPIO_Pin_11) : 
			Line = EXTI_Line_11;
			break;
		case (GPIO_Pin_12) : 
			Line = EXTI_Line_12;
			break;
		case (GPIO_Pin_13) : 
			Line = EXTI_Line_13;
			break;
		case (GPIO_Pin_14) : 
			Line = EXTI_Line_14;
			break;	
		case (GPIO_Pin_15) : 
			Line = EXTI_Line_15;
			break;
		default :
			Line = EXTI_Line_ERROR;
			break;
	}
	
	return Line;
}

/**
 * @fn Line_to_IRQn
 * @brief Return IRQn associated to Line number passed in argument
 * @param Line -> uint32_t (Line number with numerotation from EXTI_Line_0 to EXTI_Line_15)
 * @return uint8_t (IRQn corresponding to Line passed as argument)
 * @value EXTI0_IRQn to EXTI15_10_IRQn if Line is valid, (0xFF) if not
*/
uint8_t Line_to_IRQn (uint32_t Line) {
	uint8_t IRQn = 0xFF;
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
		IRQn = 0xFF;
	}
		
	return IRQn;
}

int main(void) {
	
	// objectif activer EXTI pour A0 
	
	
  return 0;
}
