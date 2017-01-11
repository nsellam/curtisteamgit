#include "Tests/test_1.hpp"

static int kmcounter;
static int carspeed;
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

Test1::Test1(QWidget *parent) : QObject(parent)
{

    kmcounter = 0; //maggle
    carspeed = 0;
    us_fl = 92;
    us_fc = 92;
    us_fr = 100;
    us_bl = 25;
    us_bc = 18;
    us_br = 12;
    battery = 92;
    error_frontobs = false;
    error_backobs = false;
    i = 0;
}

void Test1::start()
{
    if (i < 20){
        /*KmCounter*/
        kmcounter += 421;
        emit get_kmcounter(kmcounter);

        /* Battery */
        battery -= 4;
        emit get_battery(battery);

        /* Car Speed */
        if(i < 12){
            carspeed += 11;
        }else{
            carspeed -= 8;
        }
        emit get_carspeed(carspeed);

        /* Ultrasonic sensors */
        us_fl -= 4;
        emit get_us_fl(us_fl);
        us_fc -= 4;
        emit get_us_fc(us_fc);
        us_fr -= 4;
        emit get_us_fr(us_fr);
        us_bl += 4;
        emit get_us_bl(us_bl);
        us_bc += 4;
        emit get_us_bc(us_bc);
        us_br += 4;
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
