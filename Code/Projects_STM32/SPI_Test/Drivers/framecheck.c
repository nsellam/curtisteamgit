/**
 * @file framecheck.c
 * @author Curtis team
 * @brief driver layer for the CRC, the canary
 * Computes CRC/canary when sending, checks CRC/canary when receiving
 */

#include "framecheck.h"

#include <stdint.h>

#define CANARY ((uint8_t)0xCA)

/**
 * @brief calculates the checksum
 * XOR between every bit of the data
 * @param *data: pointeur to the first byte of data
 * @param len: length of the data
 * @return the CRC
 */
uint8_t frame_CRC_compute(uint8_t *pdata, size_t len) {
   int i;
   uint8_t CRC = 0;
   for (i = 0 ; i < len ; i++)
      CRC ^= pdata[i];
   return CRC;
}

/**
 * @brief checks if the CRC is correct
 * @return 0 if successful / else if error
 */
uint8_t frame_CRC_check(uint8_t *pdata, size_t len, uint8_t CRC) {
   return CRC ^ frame_CRC_compute(pdata, len);
}

/**
 * @brief calculates the canary
 * @return the canary
 */
uint8_t frame_canary_compute(void) {
   return CANARY;
}

/**
 * @brief checks if the canary is completed
 * @return 0 if successful / else if error
 */
uint8_t frame_canary_check(uint8_t canary) {
   return CANARY ^ canary;
}
