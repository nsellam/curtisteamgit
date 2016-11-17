/**
 * @file CRC.c
 * @author Curtis team
 * @brief driver layer for the CRC
 * Computes CRC when sending, checks CRC when receiving
 */

#include <stdint.h>
#include "CRC.h"

/**
 * @fn compute_CRC
 * @brief calculates the checksum
 * XOR between every bit of the data
 * @param *data: pointeur to the first byte of data
 * @param len: length of the data
 * @return the CRC
 */
uint8_t compute_CRC(uint8_t *pdata, size_t len) {
  int i;
  uint8_t CRC = 0;
  for (i = 0 ; i < len ; i++) {
    CRC ^= pdata[i];
  }
  return CRC;
}

/**
 * @fn check_CRC
 * @brief checks if the CRC is correct
 * @return 0 if successful / else if error
 */
uint8_t check_CRC(uint8_t *pdata, size_t len, uint8_t CRC) {
  return CRC ^ compute_CRC(pdata, len);
}
