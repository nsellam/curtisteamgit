/**
 * @file framecheck.c
 * @author Curtis team
 * @brief driver layer for the CRC, the Canary
 * Computes CRC/Canary when sending, checks CRC/Canary when receiving
 */

#include "framecheck.h"

#include <stdint.h>

#define CANARY ((uint8_t)0xCA)

/**
 * @fn Frame_compute_CRC
 * @brief calculates the checksum
 * XOR between every bit of the data
 * @param *data: pointeur to the first byte of data
 * @param len: length of the data
 * @return the CRC
 */
uint8_t Frame_compute_CRC(uint8_t *pdata, size_t len) {
   int i;
   uint8_t CRC = 0;
   for (i = 0 ; i < len ; i++) CRC ^= pdata[i];
   return CRC;
}

/**
 * @fn Frame_check_CRC
 * @brief checks if the CRC is correct
 * @return 0 if successful / else if error
 */
uint8_t Frame_check_CRC(uint8_t *pdata, size_t len, uint8_t CRC) {
   return CRC ^ Frame_compute_CRC(pdata, len);
}

/**
 * @fn Frame_compute_canary
 * @brief calculates the canary
 * @return the canary
 */
uint8_t Frame_compute_canary(void) {
   return CANARY;
}

/**
 * @fn Frame_check_canary
 * @brief checks if the canary is completed
 * @return 0 if successful / else if error
 */
uint8_t Frame_check_canary(uint8_t canary) {
   return CANARY ^ canary;
}
