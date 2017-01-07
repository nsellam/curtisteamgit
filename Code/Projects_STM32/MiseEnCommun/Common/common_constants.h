/**
 * @file 	common_constants.h
 * @author 	Curtis Team
 * @brief 	Constants used by all the layers
*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _COMMON_CONSTANTS_H
#define _COMMON_CONSTANTS_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
    NEUTRAL,
    FORWARD, 
    BACKWARD
} direction_TypeDef;

/* Exported constants --------------------------------------------------------*/
/**
 * @brief    Number of microseconds per second
*/
#define US_PER_S        (1.0e+06)

/**
 * @brief    Pi constant
*/
#define PI              3.141592653589793238 

/**
 * @brief    Car wheel diameter (expressed in cm)
*/
#define CAR_WHEEL_SIZE  19
 
/**
 * @def POSITION_xx
 * @brief Used to get position value in the adequate unit 
*/
#define POSITION_MM		10              // millimeters
#define POSITION_CM		1               // centimeters
#define POSITION_M_		0.01            // meters
#define	POSITION_KM		0.00001         // kilometers
#define POSITION_IN		0.393701        // inches
#define POSITION_FT		0.0328084       // feet


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif // _COMMON_CONSTANTS_H
