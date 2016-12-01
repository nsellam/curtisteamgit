#ifndef FRAMECHECK_H
#define FRAMECHECK_H

/**
 * @file framecheck.h
 * @author Curtis Team
 * @brief driver layer for the CRC, the canary
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
 * @brief calculates the checksum
 * @return the CRC
 */
uint8_t frame_CRC_compute(uint8_t *pdata, size_t len);

/**
 * @brief checks if the CRC is correct
 * @retval 0 if successful
 * @retval else if error
 */
uint8_t frame_CRC_check(uint8_t *pdata, size_t len, uint8_t crc);

/**
 * @brief puts the value of the canary
 * @return the value of the canary
 */
uint8_t frame_canary_compute(void);

/**
 * @brief checks if the canary is empty
 * @retval 0 if empty
 * @retval else if error
 */
uint8_t frame_canary_check(uint8_t canary);

/**
 * @brief effectue une correction de la trame en se basant sur le code de hamming
 * @return ??
 */
uint8_t frame_correction(uint8_t *pdata, size_t len, uint8_t crc);

#endif // FRAMECHECK_H
