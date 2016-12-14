/**
 * @file 	adc.c
 * @author 	Curtis Team
 * @brief 	Functions to handle ADCs  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t NbrOfChannelDeclared = 1;

/* Private function prototypes -----------------------------------------------*/
void ADC_Clock_Enable(ADC_TypeDef* ADCx); 

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Makes the initialization of the given Analog to Digital Converter (ADC) with the parameters specified
*/
void ADC_QuickInit(ADC_TypeDef* ADCx, uint8_t channelx, uint8_t SampleTime, uint8_t Rank) { 
    ADC_InitTypeDef ADC_InitStruct;

    ADC_DeInit(ADCx);	
   
    ADC_Clock_Enable(ADCx);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);


    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent ;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE ;
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;
    ADC_InitStruct.ADC_NbrOfChannel = NbrOfChannelDeclared;
    
    NbrOfChannelDeclared ++;
    
    //Set ADC Conversion's sample time(channel, rank, sample time)
    ADC_RegularChannelConfig(ADCx, channelx, Rank, SampleTime);

    //Reset value a init value of ADC
    ADC_Init(ADCx, &ADC_InitStruct);

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
}

/**
 * @brief Callback associated to ADC interrupts 
*/
void ADC_Callback(void) {
	// A VOIR CE QU'ON MET ICI...
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Starts the ADC Clock 
 * @param   ADC_TypeDef ADCx defines an ADC among ADC1, ADC2, and ADC3 that will be used later
 * @retval  none
*/
void ADC_Clock_Enable(ADC_TypeDef* ADCx) {
    if (ADCx == ADC1)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		else if (ADCx == ADC2)//ATTENTION: ADC2 cannot use DMA
			  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 ,ENABLE);
    else if (ADCx == ADC3)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
}
