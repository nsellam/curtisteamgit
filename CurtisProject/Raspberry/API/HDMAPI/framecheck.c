/**
 * @file framecheck.c
 * @author Curtis team
 * @brief driver layer for the CRC, the Canary
 * Computes CRC/Canary when sending, checks CRC/Canary when receiving
 */

#include "framecheck.h"

#include <stdint.h>

/**
 * @def CANARY
 * @brief the value for the canary of SPI frames
 */ 
#define CANARY ((uint8_t)0xCA)


uint8_t Frame_compute_CRC(uint8_t *pdata, size_t len) {
   int i;
   uint8_t CRC = 0;
   for (i = 0 ; i < len ; i++) CRC ^= pdata[i];
   return CRC;
}

uint8_t Frame_check_CRC(uint8_t *pdata, size_t len, uint8_t CRC) {
   return CRC ^ Frame_compute_CRC(pdata, len);
}

uint8_t Frame_compute_canary(void) {
   return CANARY;
}

uint8_t Frame_check_canary(uint8_t canary) {
   return CANARY ^ canary;
}
