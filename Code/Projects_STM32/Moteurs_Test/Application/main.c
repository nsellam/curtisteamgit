
#include "motor.h"
#include "pwm.h"

int main (void) {
   volatile int aux = 0;
   volatile float speed = 0.5;
   
   motors_init();
   motor_set_speed(speed);
   motors_start();

  while (1) {
     for(aux=0; aux<1e4; aux++){}
      motor_set_speed(speed);
  }
   
//   pwm_init(TIM1,1,20e3);
//   //active_complementary_output(TIM1, 1, 1);
//   pwm_port_init(TIM1, 1);
//   pwm_set_duty_cycle(TIM1, 1, 0.7);

   //Enable Pin
   //GPIO_QuickInit(GPIOx, ENABLE_PIN, GPIO_Mode_Out_PP);

//   pwm_enable(TIM1);
   
   
	return 0;
}

//int main (void)
//{

//  board_leds_init();
//  timer_clock_init();
//  timer_pwm_init();
//  timer_start();
//  flash_green_led_forever();
//  return 0; // there is no going back but keep the compiler happy
//}
