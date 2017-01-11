#include "LukasL/leftboard.hpp"

LeftBoard::LeftBoard(QFrame *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    LB_bar_carspeed = new QProgressBar(this);
    LB_bar_carspeed->setGeometry(SU*2, SU*2, SU*36, SU*2);
    LB_bar_carspeed->setValue(0);
    LB_bar_carspeed->setTextVisible(false);

    LB_bar_carspeed_green = new QProgressBar(this);
    LB_bar_carspeed_green->setGeometry(SU*2+4, SU*2+1, SU*11, SU*2-2);
    LB_bar_carspeed_green->setValue(0);
    LB_bar_carspeed_green->setTextVisible(false);

    LB_bar_carspeed_yellow = new QProgressBar(this);
    LB_bar_carspeed_yellow->setGeometry(SU*13+6, SU*2+1, SU*11, SU*2-2);
    LB_bar_carspeed_yellow->setValue(0);
    LB_bar_carspeed_yellow->setTextVisible(false);

    LB_bar_carspeed_red = new QProgressBar(this);
    LB_bar_carspeed_red->setGeometry(SU*24+8, SU*2+1, SU*11, SU*2-2);
    LB_bar_carspeed_red->setValue(0);
    LB_bar_carspeed_red->setTextVisible(false);

    LB_lcd_carspeed = new QLCDNumber(this);
    LB_lcd_carspeed->setGeometry(SU*20, SU*10, SU*16, SU*8);
    LB_lcd_carspeed->setFrameShape(QFrame::StyledPanel);
    LB_lcd_carspeed->setFrameShadow(QFrame::Plain);
    LB_lcd_carspeed->setLineWidth(1);
    LB_lcd_carspeed->setSmallDecimalPoint(true);
    LB_lcd_carspeed->setDigitCount(4);
    LB_lcd_carspeed->setSegmentStyle(QLCDNumber::Flat);

    LB_lcd_kmcounter = new QLCDNumber(this);
    LB_lcd_kmcounter->setGeometry(SU*6, SU*25, SU*32, SU*5);
    LB_lcd_kmcounter->setFrameShape(QFrame::StyledPanel);
    LB_lcd_kmcounter->setSmallDecimalPoint(true);
    LB_lcd_kmcounter->setDigitCount(10);
    LB_lcd_kmcounter->setSegmentStyle(QLCDNumber::Flat);

    LB_lcd_motorspeed = new QLCDNumber(this);
    LB_lcd_motorspeed->setGeometry(SU*2, SU*12, SU*6, SU*4);
    LB_lcd_motorspeed->setFrameShape(QFrame::StyledPanel);
    LB_lcd_motorspeed->setSmallDecimalPoint(true);
    LB_lcd_motorspeed->setDigitCount(4);
    LB_lcd_motorspeed->setSegmentStyle(QLCDNumber::Flat);

    LB_ctrl_motorspeed = new QSlider(this);
    LB_ctrl_motorspeed->setGeometry(SU*10, SU*6, SU*3, SU*16);
    LB_ctrl_motorspeed->setMinimum(-127);
    LB_ctrl_motorspeed->setMaximum(127);
    LB_ctrl_motorspeed->setOrientation(Qt::Vertical);

    /* Stylesheets for the widgets */

    LB_lcd_carspeed->setStyleSheet("QLCDNumber { "
                                   "color: rgb(169, 1, 0);"
                                   "border: 1px solid white;"
                                   "}");
    LB_lcd_motorspeed->setStyleSheet("QLCDNumber { "
                                     "color: rgb(169, 1, 0);"
                                     "border: 1px solid white;"
                                     "}");
    LB_lcd_kmcounter->setStyleSheet("QLCDNumber { "
                                    "color: rgb(169, 1, 0);"
                                    "border: 1px solid white;"
                                    "}");

    LB_ctrl_motorspeed->setStyleSheet("");

    LB_bar_carspeed->setStyleSheet("QProgressBar:horizontal {"
                                   "border: 1px solid white;"
                                   "background: black;"
                                   "border-radius: 2px;"
                                   "padding: 1px;"
                                   "margin-right: 4ex;"
                                   "}");

    LB_bar_carspeed_green->setStyleSheet("QProgressBar:horizontal {"
                                         "border: 0px;"
                                         "background: black;"
                                         "}"
                                         "QProgressBar::chunk:horizontal {"
                                         "background: green;"
                                         "margin-right: 2px; /* space */"
                                         "width: 3px;"
                                         "}");
    LB_bar_carspeed_yellow->setStyleSheet("QProgressBar:horizontal {"
                                          "border: 0px;"
                                          "background: black;"
                                          "}"
                                          "QProgressBar::chunk:horizontal {"
                                          "background: rgb(252, 255, 90);"
                                          "margin-right: 2px; /* space */"
                                          "width: 3px;"
                                          "}");
    LB_bar_carspeed_red->setStyleSheet("QProgressBar:horizontal {"
                                       "border: 0px;"
                                       "background: black;"
                                       "}"
                                       "QProgressBar::chunk:horizontal {"
                                       "background: rgb(165, 1, 0);"
                                       "margin-right: 2px; /* space */"
                                       "width: 3px;"
                                       "}");

}
void LeftBoard::display_carspeed(int value)
{
    if (value > 150)
    {
        LB_bar_carspeed_green->setValue(100);
        LB_bar_carspeed_yellow->setValue(100);
        LB_bar_carspeed_red->setValue(100);
    } else {
        if (value > 100)
        {
            LB_bar_carspeed_green->setValue(100);
            LB_bar_carspeed_yellow->setValue(100);
            LB_bar_carspeed_red->setValue((value-100)*2);
        }
        else {
            if (value > 50)
            {
                LB_bar_carspeed_green->setValue(100);
                LB_bar_carspeed_yellow->setValue((value-50)*2);
                LB_bar_carspeed_red->setValue(0);
            }
            else {
                LB_bar_carspeed_green->setValue(value*2);
                LB_bar_carspeed_yellow->setValue(0);
                LB_bar_carspeed_red->setValue(0);
            }
        }
    }
}
