#ifndef FRAMECHECK_H
#define FRAMECHECK_H

/**
 * @file framecheck.h
 * @author Curtis Team
 * @brief driver layer for the CRC, the Canary
 */

#include <stdint.h>
#include <stddef.h>

#define FRAME_CANARY_SIZE  1 // byte
#define FRAME_CRC_SIZE     1 // byte

#define FRAME_CHECK_SIZE (FRAME_CANARY_SIZE + FRAME_CRC_SIZE)

/************************
 *      STRUCTURES      *
 ************************/

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn Frame_CRC_Compute
 * @brief calculates the Checksum
 * @return the CRC
 */
uint8_t Frame_CRC_Compute(uint8_t *pdata, size_t len);

/**
 * @fn Frame_CRC_Check
 * @brief checks if the CRC is correct
 * @retval 0 if successful
 * @retval else if error
 */
uint8_t Frame_CRC_Check(uint8_t *pdata, size_t len, uint8_t crc);

/**
 * @fn Frame_Canary_Compute
 * @brief puts the value of the canary
 * @return the value of the canary
 */
uint8_t Frame_Canary_Compute(void);

/**
 * @fn Frame_Canary_Check
 * @brief checks if the canary is empty
 * @retval 0 if empty
 * @retval else if error
 */
uint8_t Frame_Canary_Check(uint8_t canary);

/**
 * @fn Frame_Correction
 * @brief effectue une correction de la trame en se basant sur le code de hamming
 * @return ??
 */
uint8_t Frame_Correction(uint8_t *pdata, size_t len, uint8_t crc);

#endif // FRAMECHECK_H
