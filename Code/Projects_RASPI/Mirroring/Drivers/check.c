/**
 * @file check.c
 * @author Curtis team
 * @brief driver layer for the CRC, the Canary
 * Computes CRC/Canary when sending, checks CRC/Canary when receiving
 */

#include <stdint.h>
#include "CRC.h"

#define CRC_INIT 0x00

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

int compute_CRC(uint8_t *pdata, size_t len) {
  uint8_t shift_register = CRC_INIT;
  int i;
  for (i = 0 ; i < len ; i++) {
    for (j = 8 ; j > 0 ; j--) {
      if ( (shift_register ^ pdata[i]) >> j) {
	shift_register = (shift_register >> 1) ^ polynome;
      } else {
	shift_register = shift_register >> 1;
      }
    }
  }
      
      pour i de 1 à longueur
    {
        si bit de poids fort de shiftRegister xor bitString[i] vaut 1
        {
            // décaler d'1 bit vers la gauche équivaut à multiplier par 2
            shiftRegister := (shiftRegister décalé d'1 bit vers la gauche) xor polynome
        }
        sinon
        {
            shiftRegister := (shiftRegister décalé d'1 bit vers la gauche)
        }
    }
    retourne shiftRegister
}

}

/**
 * @fn check_CRC
 * @brief checks if the CRC is correct
 * @return 0 if successful / else if error
 */
uint8_t check_CRC(uint8_t *pdata, size_t len, uint8_t CRC) {
  return CRC ^ compute_CRC(pdata, len);
}

/**
 * @fn check_canary
 * @brief checks if the canary is completed
 * @return 0 if successful / else if error
 */
uint8_t check_canary(uint8_t *pdata, size_t len, uint8_t canary) {
  return canary;
}
