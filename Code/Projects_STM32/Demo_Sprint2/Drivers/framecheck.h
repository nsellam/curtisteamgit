#ifndef FRAMECHECK_H
#define FRAMECHECK_H

/**
 * @file framecheck.h
 * @author Curtis Team
 * @brief common header to check_pi.c and check_st.c
 */

#include <stdint.h>
#include <stddef.h>

#define FRAME_CANARY_SIZE 1
#define FRAME_CRC_SIZE 1

#define FRAME_CHECK_SIZE (FRAME_CANARY_SIZE + FRAME_CRC_SIZE)

/************************
 *      STRUCTURES      *
 ************************/

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn Frame_compute_CRC
 * @brief calculates the Checksum
 * @return the CRC
 */
uint8_t Frame_compute_CRC(uint8_t *pdata, size_t len);

/**
 * @fn Frame_check_CRC
 * @brief checks if the CRC is correct
 * @retval 0 if successful
 * @retval else if error
 */
uint8_t Frame_check_CRC(uint8_t *pdata, size_t len, uint8_t crc);

/**
 * @fn Frame_compute_canary
 * @brief puts the value of the canary
 * @return the value of the canary
 */
uint8_t Frame_compute_canary(void);

/**
 * @fn Frame_check_canary
 * @brief checks if the canary is empty
 * @retval 0 if empty
 * @retval else if error
 */
uint8_t Frame_check_canary(uint8_t canary);

/**
 * @fn Frame_correction
 * @brief effectue une correction de la trame en se basant sur le code de hamming
 * @return ??
 */
uint8_t Frame_correction(uint8_t *pdata, size_t len, uint8_t crc);

#endif // FRAMECHECK_H
