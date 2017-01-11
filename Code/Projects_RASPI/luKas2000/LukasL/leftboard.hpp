#ifndef LEFTBOARD_HPP
#define LEFTBOARD_HPP

#include <QFrame>
#include <QGraphicsView>
#include <QProgressBar>
#include <QLCDNumber>
#include <QSlider>
#include "Size/size.hpp"

class LeftBoard : public QFrame
{
    Q_OBJECT

    public:
    LeftBoard(QFrame *parent = 0);
    QSlider *LB_ctrl_motorspeed;
    QLCDNumber *LB_lcd_motorspeed;
    QLCDNumber *LB_lcd_carspeed;
    QLCDNumber *LB_lcd_kmcounter;
    QProgressBar *LB_bar_carspeed;

    public slots:
    void display_carspeed(int value);

    signals:
    //signals

    private:
    QProgressBar *LB_bar_carspeed_green;
    QProgressBar *LB_bar_carspeed_yellow;
    QProgressBar *LB_bar_carspeed_red;

};


#endif // LEFTBOARD_HPP
