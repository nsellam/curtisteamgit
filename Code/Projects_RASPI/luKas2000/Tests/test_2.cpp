#include "Tests/test_2.hpp"
#include "Tests/test_hdmapi.h"

static int kmcounter;
static int carspeed;
static int motorspeed;
static int us_fl;
static int us_fc;
static int us_fr;
static int us_bl;
static int us_bc;
static int us_br;
static int battery;
static bool error_frontobs;
static bool error_backobs;

static int i;

Test2::Test2(QWidget *parent) : QObject(parent)
{
    error_frontobs = false;
    error_backobs = false;
    i = 0;
}

void Test2::start()
{
    if (i < 20){

        motorspeed = static_cast<int>(get_motor_speed_data_test());
        emit get_motorspeed(motorspeed);

        kmcounter = static_cast<int>(get_travelled_distance_test());
        emit get_kmcounter(kmcounter);

        battery = get_battery_state_test();
        emit get_battery(battery);

        carspeed = static_cast<int>(get_car_speed_test());
        emit get_carspeed(carspeed);

        us_fl = static_cast<int>(get_ultrasonic_data_test(2));
        emit get_us_fl(us_fl);
        us_fc = static_cast<int>(get_ultrasonic_data_test(1));
        emit get_us_fc(us_fc);
        us_fr = static_cast<int>(get_ultrasonic_data_test(0));
        emit get_us_fr(us_fr);
        us_bl = static_cast<int>(get_ultrasonic_data_test(5));
        emit get_us_bl(us_bl);
        us_bc = static_cast<int>(get_ultrasonic_data_test(4));
        emit get_us_bc(us_bc);
        us_br = static_cast<int>(get_ultrasonic_data_test(3));
        emit get_us_br(us_br);

        if ((us_fc <= 15) or (us_fl <= 15) or (us_fr <= 15))
        {
            error_frontobs = true;
            emit get_error_frontobs();
        }

        if ((us_fc <= 15) or (us_fl <= 15) or (us_fr <= 15))
        {
            error_backobs = true;
            emit get_error_backobs();
        }
        i++;
    }
}

void Test2::setMotorSpeed(int value)
{
    set_motor_speed_data_test(value);
}
