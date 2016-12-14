/**
 * @file 	spi.c
 * @author 	Curtis Team
 * @brief 	Functions to handle SPI  
 */
 
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief Makes the initialization of the SPI with the parameters specified
 * @param SPI_Mode uint16_t Mode (master or slave) chosen for STM32 (usage : SPI_Mode_Master or SPI_Mode_Slave)
*/
void SPI_QuickInit(uint16_t SPI_Mode) {
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 0; // no CRC
	SPI_Init(SPI2, &SPI_InitStructure);
}


/**
 * @brief Callback associated to SPI interrupts 
*/
void SPI_Callback(SPI_TypeDef SPIx) {
	// A VOIR CE QU'ON MET ICI...
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief   Handler associated to SPI
*/
void SPI_ITHandler(SPI_TypeDef SPIx) {
    SPI_Callback(SPIx);
}
