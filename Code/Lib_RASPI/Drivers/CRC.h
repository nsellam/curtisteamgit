#ifndef CRC_H
#define CRC_H

/**
 * @file CRC.h
 * @author Curtis Team
 * @brief common header to CRC_pi and CRC_st
 * 
 */

#include <stdint.h>
#include <stddef.h>

/************************
 *      STRUCTURES      *
 ************************/

/************************
 *      FUNCTIONS       *
 ************************/

/**
 * @fn compute_CRC
 * @brief calculates the Checksum
 * @return 0 if successful / -1 if error
 */
uint8_t compute_CRC(uint8_t *pdata, size_t len) ;
/**
 * @fn check_CRC
 * @brief checks if the CRC is correct
 * @return 0 if successful / -1 if error
 */
uint8_t check_CRC(uint8_t *pdata, size_t len, uint8_t CRC);
#endif //CRC_H
