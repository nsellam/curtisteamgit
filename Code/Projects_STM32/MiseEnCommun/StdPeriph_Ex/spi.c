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
void SPI_ClockEnable(SPI_TypeDef SPIx);

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Makes the initialization of the SPI with the parameters specified
 * @param SPI_Mode uint16_t Mode (master or slave) chosen for STM32 (usage : SPI_Mode_Master or SPI_Mode_Slave)
*/
void SPI_QuickInit(SPI_TypeDef SPIx, uint16_t SPI_Mode) {
	SPI_InitTypeDef SPI_InitStructure;
    
    SPI_ClockEnable(SPIx);
    
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

    //SPI_Cmd(SPIx, ENABLE);
}

__weak void SPI_Callback(SPI_TypeDef SPIx) {}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief 	Enables clock on the adequate GPIO
 * @param 	SPIx SPI_TypeDef (SPI to switch on the clock)
 * @retval 	None
*/
void SPI_ClockEnable(SPI_TypeDef SPIx) {
            if (&SPIx == SPI1) RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    else    if (&SPIx == SPI2) RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    else{}
}

/**
 * @brief   Handler associated to SPI
*/
void SPI_ITHandler(SPI_TypeDef SPIx) {
    SPI_Callback(SPIx);
}
