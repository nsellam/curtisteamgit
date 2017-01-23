/**
 * @file application_code.c
 * @author Curtis Team
 * @brief Application using our API - dedicated to the user of our API
 */

/********************************/
/*       LIBRARIES              */
/********************************/
#include <stdio.h>
#include <assert.h>

/********************************/
/*       INCLUDES               */
/********************************/

#include <application_code.h>
#include <data_interface.h>
#include <xpsapi.h>
#include <hdmapi.h>

/********************************/
/*       DEFINES                */
/********************************/



/********************************/
/*       MAIN                   */
/********************************/



void * Application(void* arg) {

printf("%i", sizeof (side_TypeDef));


sleep(1);
  set_enable_motors_control((uint8_t)(1));
sleep(1);
  set_car_direction(LEFT);
sleep(1);
  set_car_direction(RIGHT);
  set_enable_motors_control((uint8_t)(0));
sleep(1);
  set_enable_motors_control((uint8_t)(1));
sleep(1);
  set_motor_speed(44);
sleep(1);
  set_motor_speed(0);
sleep(1);
  set_motor_speed(200);

sleep(1);
  //goForward(100.0, 50); 

  //goForward(-300.0, 70);  
display();
  //goForward(300.0, 20);  

  //goForward(300.0, 50);   

  


  return 0;
}