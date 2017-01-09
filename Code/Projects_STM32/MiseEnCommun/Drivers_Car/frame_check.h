/**
 * @file    frame_check.h
 * @author  Curtis Team
 * @brief   Headers of functions to ensure frame checking
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FRAME_CHECK_H
#define _FRAME_CHECK_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t FrameCheck_computeCRC(uint8_t *pdata, size_t len);
uint8_t FrameCheck_checkCRC(uint8_t *pdata, size_t len, uint8_t crc);
uint8_t FrameCheck_computeCanary(void);
uint8_t FrameCheck_checkCanary(uint8_t canary);
uint8_t FrameCheck_frameCorrection(uint8_t *pdata, size_t len, uint8_t crc);

#endif // _FRAME_CHECK_H
