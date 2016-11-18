#ifndef CHECK_H
#define CHECK_H

/**
 * @file check.h
 * @author Curtis Team
 * @brief common header to check_pi.c and check_st.c
 */

#include <stdint.h> //for the uint8_t type
#include <stddef.h> //for the size_t type

/************************
 *      STRUCTURES      *
 ************************/

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn compute_crc
 * @brief calculates the Checksum
 * @return the CRC
 */
uint8_t compute_crc(uint8_t *pdata, size_t len);

/**
 * @fn compute_canary
 * @brief puts the value of the canary
 * @return the value of the canary
 */
uint8_t compute_canary(void);

/**
 * @fn check_crc
 * @brief checks if the CRC is correct
 * @retval 0 if successful
 * @retval else if error
 */
uint8_t check_crc(uint8_t *pdata, size_t len, uint8_t crc);

/**
 * @fn check_canary
 * @brief checks if the canary is empty
 * @retval 0 if empty
 * @retval else if error
 */
uint8_t check_canary(uint8_t can);

/**
 * @fn correction
 * @brief effectue une correction de la trame en se basant sur le code de hamming
 * @return ??
 */
uint8_t correction(uint8_t *pdata, size_t len, uint8_t crc);

#endif //CHECK_H
