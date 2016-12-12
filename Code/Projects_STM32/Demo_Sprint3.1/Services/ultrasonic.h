
#include <stdint.h>
#include <math.h>

#include <stm32f10x.h>
#include "pwm.h"
#include "capture.h"


void Ultrasonic_Init(void);

void Ultrasonic_Start(void);

void Ultrasonic_Stop(void);

float Ultrasonic_GetDistance(void);

