#include <stdint.h>
#include <stm32f10x.h>

#include "systick.h"
#include "adc.h"
#include "pwm.h"
#include "spi.h"


void HDMAPI_Example(void) {
    SysTick_QuickInit();
    
    PWM_Example();
    
    ADC_Example();

    SPI_QuickInit(*SPI1, SPI_Mode_Slave);
    while (1) {}
}
