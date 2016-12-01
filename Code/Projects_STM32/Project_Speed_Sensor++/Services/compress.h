/**
 * @file compress.h
 * @author Curtis Team
 * @brief Headers of functions to compress data for sending 
 */
 
#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdint.h>
#include "car.h"

/**
 * @def COMPRESSED_POSITION_MAX
 * @brief Max value possible after position compression
*/
#define COMPRESSED_POSITION_MAX		((0x01 << CAR_MESSAGE_LENGTH) - 1)

/**
 * @def COMPRESSED_POSITION_MIN
 * @brief Min value possible after position compression
*/
#define COMPRESSED_POSITION_MIN		0x00

/**
 * @def COMPRESSED_POSITION_ZERO
 * @brief Value in compressed result for position equal to zero
*/
#define COMPRESSED_POSITION_ZERO	(uint8_t) (((COMPRESSED_POSITION_MAX + COMPRESSED_POSITION_MIN) / 2) + 1)

/**
 * @def COMPRESSED_SPEED_MAX
 * @brief Max value possible after speed compression
*/
#define COMPRESSED_SPEED_MAX			((0x01 << CAR_MESSAGE_LENGTH) - 1)

/**
 * @def COMPRESSED_SPEED_MIN
 * @brief Min value possible after speed compression
*/
#define COMPRESSED_SPEED_MIN			0x00

/**
 * @def COMPRESSED_SPEED_ZERO
 * @brief Value in compressed result for speed equal to zero
*/
#define COMPRESSED_SPEED_ZERO			(uint8_t) (((COMPRESSED_POSITION_MAX + COMPRESSED_POSITION_MIN) / 2) + 1)

/**
 * @fn compress_speed
 * @brief Convert the float given as a uint8_t (to easily send via SPI)
 * @param speed -> float (speed to compress) : it is recommended to use defined units such as SPEED_CM_S, SPEED_MM_S, SPEED_M_S, SPEED_KM_H, SPEED_FT_S,...
 * @param unit -> float (unit of speed parameter)
 * @return uint8_t (compressed speed)
*/
uint8_t compress_speed (float speed, float unit);

/**
 * @fn compress_position
 * @brief Convert the float given as a uint8_t (to easily send via SPI)
 * @param position -> float (speed to compress) : it is recommended to use defined units such as POSITION_MM, POSITION_CM, POSITION_M, POSITION_IN, POSITION_FT,...
 * @param unit -> float (unit of position parameter)
 * @return uint8_t (compressed position)
*/
uint8_t compress_position (float position, float unit);

#endif //COMPRESS_H
