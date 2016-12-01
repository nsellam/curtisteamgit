/**
 * @file uncompress.h
 * @author Curtis Team
 * @brief Headers of functions to uncompress received data 
 */
 
#ifndef UNCOMPRESS_H
#define UNCOMPRESS_H

#include <stdint.h>
#include "stm32f10x.h"

float uncompress_speed (uint16_t speed, float unit);

float uncompress_position (uint8_t position, float unit);

#endif //UNCOMPRESS_H