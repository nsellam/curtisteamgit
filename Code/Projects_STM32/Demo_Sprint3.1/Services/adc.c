/**
 * @file adc.c
 * @author Curtis Team
 * @brief Service functions for ADC
 */
 
 /********************************/
/*       LIBRARIES              */
/********************************/
#include "adc.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_it.h"
#include "data.h"

/********************************/
/*         CONSTANTS            */
/********************************/

/**
* @def NbrOfChannel
* @brief Two channels of ADC will be used for left and right motors
*/
#define NbrOfChannel ((uint8_t) 0x02)

/**
* @def Rank_1_ADC_Channel, Rank_2_ADC_Channel
* @brief rank of two ADC channels
*/
#define Rank_1_ADC_Channel ((uint8_t) 0x01)
#define Rank_2_ADC_Channel ((uint8_t) 0x02)

/**
* @def Buffer_size
* @brief Size of DMA Buffer to stock the ADC values
*/
#define Buffer_size ((uint8_t) 2)

/**
* @var ADC_values
* @brief Create memory address for DMA stock table whose wize is defined by Buffer_size
*/
volatile uint16_t ADC_values[Buffer_size];

/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @fn Init_ADC
* @brief Initializes and strat the ADC converter 
* @param GPIO_TypeDef*, GPIO_pin number: two GPIO pins that used for ADC
* @param ADC_TypeDef*, ADC_Channel number, ADC_SampleTime£ºdefine an ADC among ADC1, ADC2, and ADC3 that will be used later; the channels of ADC associated and their sample time
* @param DMA_Channel_TypeDef*: define a DMA and its channel for ADC used
* @return void
*/
void Init_ADC (GPIO_TypeDef* GPIO1, uint16_t GPIO_Pin1,GPIO_TypeDef* GPIO2, uint16_t GPIO_Pin2, ADC_TypeDef* ADCx, uint8_t channel1, uint8_t channel2,uint8_t ADC_SampleTime,DMA_Channel_TypeDef* DMAy_Channelx)
{
    //structure declaration  
  GPIO_InitTypeDef GPIO_InitStruct1;
  GPIO_InitTypeDef GPIO_InitStruct2;  
	ADC_InitTypeDef ADC_InitStruct;
	 
    //create DMA structure
    DMA_InitTypeDef  DMA_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
		//Reset ADCx
	  ADC_DeInit(ADCx);
	
   
    //Enable Rcc clock for ADC interface
	  Port_GPIO_Clock_Enable(GPIO1);
	  Port_GPIO_Clock_Enable(GPIO2);
    ADC_Clock_Enable(ADCx);
	//enable DMA1 clock
    DMA_Clock_Enable(DMAy_Channelx);
	
	//GPIO structure
	  GPIO_InitStruct1.GPIO_Pin = GPIO_Pin1;// Set gpio pin for adc
    GPIO_InitStruct1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIO1, &GPIO_InitStruct1);
	
	  GPIO_InitStruct2.GPIO_Pin = GPIO_Pin2;// Set gpio pin for adc
    GPIO_InitStruct2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct2.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIO2, &GPIO_InitStruct2);
	
        
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent ;// ADC1 and ADC3 are independent
		if(NbrOfChannel == 0x01)
			ADC_InitStruct.ADC_ScanConvMode = DISABLE ;//ADC works in single mode
		else ADC_InitStruct.ADC_ScanConvMode = ENABLE ; // ADC works in scan mode for multiple channel
		
	  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;//Conversion is in continuous mode
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;// Aligne in Right
    ADC_InitStruct.ADC_NbrOfChannel = NbrOfChannel;// Channel of ADC
		
		//Set ADC Conversion's sample time(channel, rank, sample time)
    ADC_RegularChannelConfig(ADCx, channel1, Rank_1_ADC_Channel, ADC_SampleTime);
		ADC_RegularChannelConfig(ADCx, channel2, Rank_2_ADC_Channel, ADC_SampleTime);
    
    //Reset value a init value of ADC
    ADC_Init(ADCx, &ADC_InitStruct);
    //DMA Request
		ADC_DMACmd(ADCx, ENABLE);
    //Enable ADC
    ADC_Cmd(ADCx, ENABLE);
    //Reset of ADC Calibration register
    ADC_ResetCalibration(ADCx);
    //Wait until the reset of register is finished
    while (ADC_GetResetCalibrationStatus(ADCx));
    //ADC starts to calibrate
    ADC_StartCalibration(ADCx);
    //Wait until the calibration is done
    while (ADC_GetCalibrationStatus(ADCx));
		
		//reset DMA1 channe1 to default values;
    DMA_DeInit(DMAy_Channelx);
		//source and destination start addresses
   
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADCx->DR);
		
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_values;
    //Location assigned to peripheral register will be source
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    //chunk of data to be transfered
    DMA_InitStructure.DMA_BufferSize = Buffer_size;
    //source address increment disable
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //automatic memory destination increment enable
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //source and destination data size word=32bit
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;
    //setting normal mode (non circular)
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    //medium priority
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    //channel will be used for memory to memory transfer
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		
		//send values to DMA registers
    DMA_Init(DMAy_Channelx, &DMA_InitStructure);
    // Enable DMA-Channel Transfer Complete interrupt
    //DMA_ITConfig(DMAy_Channelx, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMAy_Channelx, ENABLE); //Enable the DMA- Channel
		
    //Config NVIC structure
    //Enable DMA1 channel IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		//Start ADC Software Conversion
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
* @fn Get_ADC_Mot_G
* @brief get the ADC value from left motor
* @param void
* @return uint16_t; digital value of current
*/
uint16_t Get_ADC_Mot_G(){
	return ADC_values[0];
}

/**
* @fn Get_ADC_Mot_D
* @brief get the ADC value from right motor
* @param void
* @return uint16_t; digital value of current
*/
uint16_t Get_ADC_Mot_D(){
	return ADC_values[1];
}



/**
* @fn Port_GPIO_Clock_Enable
* @brief Start the GPIO Clock 
* @param GPIO_TypeDef*: define a GPIO pin for ADC
* @return void
*/
void Port_GPIO_Clock_Enable(GPIO_TypeDef* GPIOx) {
    if (GPIOx == GPIOA)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    else if (GPIOx == GPIOB)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    else if (GPIOx == GPIOC)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    else if (GPIOx == GPIOD)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
}

/**
* @fn ADC_Clock_Enable
* @brief Start the ADC Clock 
* @param ADC_TypeDef*£ºdefine an ADC among ADC1, ADC2, and ADC3 that will be used later
* @return void
*/
void ADC_Clock_Enable(ADC_TypeDef* ADCx) {
    if (ADCx == ADC1)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		else if (ADCx == ADC2)//ATTENTION: ADC2 cannot use DMA
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 ,ENABLE);
    else if (ADCx == ADC3)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
}

/**
* @fn DMA_Clock_Enable
* @brief Start the DMA Clock 
* @param DMA_Channel_TypeDef*: define a DMA channel for ADC use 
* @return void
*/
void DMA_Clock_Enable(DMA_Channel_TypeDef* DMAy_Channelx) {
    if ((DMAy_Channelx == DMA1_Channel1)||(DMAy_Channelx ==DMA1_Channel2)||(DMAy_Channelx ==DMA1_Channel3)||(DMAy_Channelx ==DMA1_Channel4)||(DMAy_Channelx ==DMA1_Channel5)||(DMAy_Channelx ==DMA1_Channel6)||(DMAy_Channelx ==DMA1_Channel7))
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    else if ((DMAy_Channelx == DMA2_Channel1)||(DMAy_Channelx ==DMA2_Channel2)||(DMAy_Channelx ==DMA2_Channel3)||(DMAy_Channelx ==DMA2_Channel4)||(DMAy_Channelx ==DMA2_Channel5))
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2,ENABLE);
}

