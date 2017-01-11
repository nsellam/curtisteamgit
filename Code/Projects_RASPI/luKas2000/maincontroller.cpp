#include "maincontroller.hpp"
#include "hdmapi.h"
#include <QtCore>

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
static bool critical_battery;

MainController::MainController(QWidget *parent) : QThread(parent)
{
    error_frontobs = false;
    error_backobs = false;
    critical_battery = false;
}

void MainController::run()
{
    while(1) {
        msleep(100);

        motorspeed = static_cast<int>(get_motor_speed_data());
        if (motorspeed > 127) {
            motorspeed -= 255;
        }
        emit get_motorspeed(motorspeed);

        kmcounter = static_cast<int>(get_travelled_distance());
        emit get_kmcounter(kmcounter);

        battery = get_battery_state();
        emit get_battery(battery);

        if (battery < 15) {
            emit get_critical_battery();
        }

        carspeed = static_cast<int>(get_car_speed());
        emit get_carspeed(carspeed);

        us_fl = static_cast<int>(get_ultrasonic_data(2));
        emit get_us_fl(us_fl);
        us_fc = static_cast<int>(get_ultrasonic_data(1));
        emit get_us_fc(us_fc);
        us_fr = static_cast<int>(get_ultrasonic_data(0));
        emit get_us_fr(us_fr);
        us_bl = static_cast<int>(get_ultrasonic_data(5));
        emit get_us_bl(us_bl);
        us_bc = static_cast<int>(get_ultrasonic_data(4));
        emit get_us_bc(us_bc);
        us_br = static_cast<int>(get_ultrasonic_data(3));
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
    }
}

void MainController::setMotorSpeed(int value)
{
    set_motor_speed_data(value);
}
