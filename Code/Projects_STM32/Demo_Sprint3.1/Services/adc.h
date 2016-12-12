/**
 * @file adc.h
 * @author Curtis team
 * @brief Service library for ADC that allows to convert output current of motors to digital values 
 */

#ifndef _ADC_H_
#define _ADC_H_

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stm32f10x_conf.h>
#include <stm32f10x_it.h>


/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @def UPDATE_MOTOR_CURRENT_PERIOD
* @brief Update motor's current data period in the data.h
*/
#define UPDATE_MOTOR_CURRENT_PERIOD 1 // ms

/**
* @fn DMA_Clock_Enable
* @brief Start the DMA Clock 
* @param DMA_Channel_TypeDef*: define a DMA channel for ADC use 
* @return void
*/
void DMA_Clock_Enable(DMA_Channel_TypeDef* DMAy_Channelx);

/**
* @fn ADC_Clock_Enable
* @brief Start the ADC Clock 
* @param ADC_TypeDef*£ºdefine an ADC among ADC1, ADC2, and ADC3 that will be used later
* @return void
*/
void ADC_Clock_Enable(ADC_TypeDef* ADCx);

/**
* @fn Port_GPIO_Clock_Enable
* @brief Start the GPIO Clock 
* @param GPIO_TypeDef*: define a GPIO pin for ADC
* @return void
*/
void Port_GPIO_Clock_Enable(GPIO_TypeDef* GPIOx);

/**
* @fn Init_ADC
* @brief Initializes and strat the ADC converter 
* @param GPIO_TypeDef*, GPIO_pin number: two GPIO pins that used for ADC
* @param ADC_TypeDef*, ADC_Channel number, ADC_SampleTime£ºdefine an ADC among ADC1, ADC2, and ADC3 that will be used later; the channels of ADC associated and their sample time
* @param DMA_Channel_TypeDef*: define a DMA and its channel for ADC used
* @return void
*/
void Init_ADC(GPIO_TypeDef* GPIO1, uint16_t GPIO_Pin1,GPIO_TypeDef* GPIO2, uint16_t GPIO_Pin2, ADC_TypeDef* ADCx, uint8_t channel1, uint8_t channel2,uint8_t ADC_SampleTime,DMA_Channel_TypeDef* DMAy_Channelx);

/**
* @fn Get_ADC_Mot_G
* @brief get the ADC value from left motor
* @param void
* @return uint16_t; digital value of current
*/
uint16_t Get_ADC_Mot_G(void);

/**
* @fn Get_ADC_Mot_D
* @brief get the ADC value from right motor
* @param void
* @return uint16_t; digital value of current
*/
uint16_t Get_ADC_Mot_D(void);



#endif // _ADC_H_
