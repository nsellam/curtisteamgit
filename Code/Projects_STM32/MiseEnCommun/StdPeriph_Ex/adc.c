/**
 * @file    adc.c
 * @author  Curtis Team
 * @brief   Functions to handle ADCs  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/**
 * @brief     GPIOMode_TypeDef recommended to initialize GPIO for ADC
*/ 
#define GPIO_MODE_ADC           GPIO_Mode_AIN

/**
 * @brief     Specified port is not valid (only GPIOA, GPIOB an GPIOC are available) 
*/ 
#define ERROR_INVALID_PORT   (uint8_t) -1

/**
 * @brief     Specified pin can't be use on this port for ADC 
*/ 
#define ERROR_INVALID_PIN   (uint8_t) -2

/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t NbrOfChannelDeclared = 0;

/* Private function prototypes -----------------------------------------------*/
void ADC_Clock_Enable(ADC_TypeDef* ADCx); 
uint8_t GPIOPin2ADCChannel (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief   Makes the initialization of the given Analog to Digital Converter (ADC) with the parameters specified
 * @param   ADCx ADC unit to use to perform analog to digital conversions
 * @param   GPIOx Port of the input to consider
 * @param   GPIO_Pin_x Number of the pin to consider
 * @param   SampleTime Averaging time (in number of cycles)
 *   This parameter can be one of the following values:
 *     @arg ADC_SampleTime_1Cycles5: Sample time equal to 1.5 cycles
 *     @arg ADC_SampleTime_7Cycles5: Sample time equal to 7.5 cycles
 *     @arg ADC_SampleTime_13Cycles5: Sample time equal to 13.5 cycles
 *     @arg ADC_SampleTime_28Cycles5: Sample time equal to 28.5 cycles	
 *     @arg ADC_SampleTime_41Cycles5: Sample time equal to 41.5 cycles	
 *     @arg ADC_SampleTime_55Cycles5: Sample time equal to 55.5 cycles	
 *     @arg ADC_SampleTime_71Cycles5: Sample time equal to 71.5 cycles	
 *     @arg ADC_SampleTime_239Cycles5: Sample time equal to 239.5 cycles
 * @param   Rank Place of this conversion in the conversions sequence
 * @retval  int (error detected while computing initialization)
 * @return  If everything went right ADC_NO_ERROR, if not ADC_ERROR_PIN or ADC_ERROR_PORT
*/
int ADC_QuickInit(ADC_TypeDef* ADCx, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, uint8_t SampleTime, uint8_t Rank) { 
    ADC_InitTypeDef ADC_InitStruct;
    
    uint8_t channelx = GPIOPin2ADCChannel (GPIOx, GPIO_Pin_x);
    
    if (channelx == ERROR_INVALID_PORT) return ADC_ERROR_PORT; else{}
    if (channelx == ERROR_INVALID_PIN)  return ADC_ERROR_PIN ; else{} 
    
    GPIO_QuickInit(GPIOx, GPIO_Pin_x, GPIO_MODE_ADC);
    
    ADC_DeInit(ADCx);    
   
    ADC_Clock_Enable(ADCx);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    NbrOfChannelDeclared ++;

    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent ;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE ;
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;
    ADC_InitStruct.ADC_NbrOfChannel = NbrOfChannelDeclared;
    
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
    
    return ADC_NO_ERROR;
}

/**
 * @brief Callback associated to ADC interrupts 
*/
void ADC_Callback(void) {
    // UNUSED
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

uint8_t GPIOPin2ADCChannel (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x) {
    if (GPIOx == GPIOA) { 
        switch (GPIO_Pin_x) { 
            case (GPIO_Pin_0) : return ADC_Channel_0; break;
            case (GPIO_Pin_1) : return ADC_Channel_1; break;
            case (GPIO_Pin_2) : return ADC_Channel_2; break;
            case (GPIO_Pin_3) : return ADC_Channel_3; break;
            case (GPIO_Pin_4) : return ADC_Channel_4; break;
            case (GPIO_Pin_5) : return ADC_Channel_5; break;
            case (GPIO_Pin_6) : return ADC_Channel_6; break;
            case (GPIO_Pin_7) : return ADC_Channel_7; break;
            default :           return ERROR_INVALID_PIN; break;
        }
    }
    else if (GPIOx == GPIOB) {
        switch (GPIO_Pin_x) { 
            case (GPIO_Pin_0) : return ADC_Channel_8; break;
            case (GPIO_Pin_1) : return ADC_Channel_9; break;
            default :           return ERROR_INVALID_PIN; break;
        }
    }
    else if (GPIOx == GPIOC) {
        switch (GPIO_Pin_x) { 
            case (GPIO_Pin_0) : return ADC_Channel_10; break;
            case (GPIO_Pin_1) : return ADC_Channel_11; break;
            case (GPIO_Pin_2) : return ADC_Channel_12; break;
            case (GPIO_Pin_3) : return ADC_Channel_13; break;
            case (GPIO_Pin_4) : return ADC_Channel_14; break;
            case (GPIO_Pin_5) : return ADC_Channel_15; break;
            default :           return ERROR_INVALID_PIN; break;
        }
    } 
    else { return ERROR_INVALID_PORT;}
}
