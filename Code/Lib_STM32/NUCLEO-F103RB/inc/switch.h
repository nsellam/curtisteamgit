#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>

/**
 * @fn switch_config(void)
 * @brief external pull-up switch
 */
void Switch_Config(void);

/**
 * @fn switch_is_pressed(void)
 * @brief
 * @return state of the switch
 * @retval 1 pressed
 * @retval 0 pressed
 */
uint8_t Switch_IsPressed(void);

#endif // SWITCH_H
