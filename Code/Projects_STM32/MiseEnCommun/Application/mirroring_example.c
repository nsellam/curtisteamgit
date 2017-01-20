/**
 * @file	mirroring_example.c
 * @author	Curtis Team
 * @brief	Template for all the files of the project  
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stm32f10x.h>
#include "mirroring.h"
#include "data_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Public variables ----------------------------------------------------------*/ 
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
 * @brief  Example for the Mirroring module
 * @param  None
 * @retval None
*/
void Mirroring_Example(void) {
   Mirroring_Init();
   pDataITF_STM->ultrasonic_sensors[0] = 10;
   pDataITF_STM->battery_level = 91;
   Mirroring_Start();
   while(1){};
}


/* Private functions ---------------------------------------------------------*/
