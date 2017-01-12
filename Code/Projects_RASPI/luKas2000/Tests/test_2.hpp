#ifndef TEST_2_HPP
#define TEST_2_HPP

#include <QObject>
#include <QFrame>
#include <QWidget>
#include <cstdint>

class Test2 : public QObject
{
    Q_OBJECT

    public:
    Test2(QWidget *parent = 0);

    public slots:
    void start();
    void setMotorSpeed(int value);

    signals:
    void get_kmcounter(int kmcounter);
    void get_carspeed(int carspeed);
    void get_motorspeed(int motorspeed);
    void get_us_fl(int us_fl);
    void get_us_fc(int us_fc);
    void get_us_fr(int us_fr);
    void get_us_bl(int us_bl);
    void get_us_bc(int us_bc);
    void get_us_br(int us_br);
    void get_battery(int battery);
    void get_error_frontobs();
    void get_error_backobs();

    private:

};

#endif // TEST_2_HPP
