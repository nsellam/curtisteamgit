#include "LukasC/error_left.hpp"

ErrorLeft::ErrorLeft(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    QFont error_font("Digital-7", 14, QFont::Bold, true);

    CB_errorleft1 = new QPushButton(this);
    CB_errorleft1->setGeometry(SU, SU*7, SU*8, SU*4);
    CB_errorleft1->setFont(error_font);

    CB_errorleft2 = new QPushButton(this);
    CB_errorleft2->setGeometry(SU, SU*12, SU*8, SU*4);
    CB_errorleft2->setFont(error_font);

    CB_errorleft3 = new QPushButton(this);
    CB_errorleft3->setGeometry(SU, SU*17, SU*8, SU*4);
    CB_errorleft3->setFont(error_font);

    CB_errorleft1->setStyleSheet("QPushButton {"
                                 "background-color: rgb(252, 255, 90);"
                                 "border-style: outset;"
                                 "border-width: 1px;"
                                 "border-radius: 10px;"
                                 "border-color: white;"
                                 "}");
    CB_errorleft2->setStyleSheet("QPushButton {"
                                 "background-color: rgb(252, 255, 90);"
                                 "border-style: outset;"
                                 "border-width: 1px;"
                                 "border-radius: 10px;"
                                 "border-color: white;"
                                 "}");
    CB_errorleft3->setStyleSheet("QPushButton {"
                                 "background-color: rgb(252, 255, 90);"
                                 "border-style: outset;"
                                 "border-width: 1px;"
                                 "border-radius: 10px;"
                                 "border-color: white;"
                                 "}");

}


void ErrorLeft::display_critical_battery()
{
    CB_errorleft1->setText("BATTERY LOW");
    CB_errorleft1->setStyleSheet("QPushButton {"
                                  "color: black;"
                                  "background-color: rgb(165, 1, 0);"
                                  "border-style: outset;"
                                  "border-width: 1px;"
                                  "border-radius: 10px;"
                                  "border-color: black;"
                                  "}");

}
