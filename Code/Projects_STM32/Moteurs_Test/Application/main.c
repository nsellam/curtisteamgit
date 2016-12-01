
#include "motor.h"
#include "pwm.h"

int main (void) {
  volatile int aux = 0;
   volatile float speed = 1;
   
   pwm_init(TIM1,1,50e3);
   active_complementary_output(TIM1, 1, 1);
   pwm_port_init(TIM1, 1);
   pwm_set_duty_cycle(TIM1, 1, 0.5);
   pwm_enable(TIM1);

//   motors_init();
//   motors_start();
   
   
//  while (1) {
//      motor_set_speed(speed);
//  }
//   motors_stop();
//   motors_start();
   while(1);
   
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
