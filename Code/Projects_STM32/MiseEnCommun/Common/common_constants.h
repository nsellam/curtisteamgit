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

typedef enum {
  LEFT = 1,
  NONE = 0,
  RIGHT = -1
} side_TypeDef;


/* Exported constants --------------------------------------------------------*/
/**
 * @brief    Number of microseconds per second
*/
#define US_PER_S                (1.0e+06)

/**
 * @brief    Pi constant
*/
#define PI                      3.141592653589793238 

/**
 * @brief    Car wheel diameter (expressed in cm)
*/
#define CAR_WHEEL_SIZE          19

/**
 * @brief    Car maximum forward speed (expressed in cm/s)
*/
#define CAR_MAX_SPEED 		    138.889	                // cm/s  => 138.889 cm/s = 5 km/h

/**
 * @brief    Car maximum backward speed (expressed in cm/s)
*/
#define CAR_MIN_SPEED			-CAR_MAX_SPEED			// cm/s

/**
 * @brief Value given if car browses instantly the distance between two samples
*/
#define INFINITE                999999.99

/**
 * @def POSITION_xx
 * @brief Used to get position value in the adequate unit 
*/
#define POSITION_MM		        10                      // millimeters
#define POSITION_CM		        1                       // centimeters
#define POSITION_M_		        0.01                    // meters
#define	POSITION_KM		        0.00001                 // kilometers
#define POSITION_IN		        0.393701                // inches
#define POSITION_FT		        0.0328084               // feet

/**
 * @def SPEED_xxxx 
 * @brief Used to get speed value in the adequate unit
 */
#define SPEED_MM_S		        10                      // millimeters per second
#define SPEED_CM_S 		        1                       // centimeters per second
#define SPEED_M__S		        0.01                    // meters per second
#define SPEED_KM_S		        0.00001                 // kilometers per second
#define SPEED_KM_H		        0.036                   // kilometers per hour
#define SPEED_FT_S		        0.0328084               // feet per second
#define SPEED_MI_H		        0.02236936		        // miles per hour
#define SPEED_MI_S		        0.0000062137            // miles per second
#define SPEED_KNOT		        0.01943845  	        // knots

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif // _COMMON_CONSTANTS_H
