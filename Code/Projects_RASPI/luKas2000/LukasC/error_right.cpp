#include "LukasC/error_right.hpp"

ErrorRight::ErrorRight(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    QFont error_font("Digital-7", 8, QFont::Bold, true);

    CB_errorright1 = new QPushButton(this);
    CB_errorright1->setGeometry(SU, SU*7, SU*8, SU*4);
    CB_errorright1->setFont(error_font);

    CB_errorright2 = new QPushButton(this);
    CB_errorright2->setGeometry(SU, SU*12, SU*8, SU*4);
    CB_errorright2->setFont(error_font);

    CB_errorright3 = new QPushButton(this);
    CB_errorright3->setGeometry(SU, SU*17, SU*8, SU*4);
    CB_errorright3->setFont(error_font);

    CB_errorright1->setStyleSheet("QPushButton {"
                                 "background-color: rgb(252, 255, 90);"
                                 "border-style: outset;"
                                 "border-width: 1px;"
                                 "border-radius: 10px;"
                                 "border-color: white;"
                                 "}");
    CB_errorright2->setStyleSheet("QPushButton {"
                                 "background-color: rgb(252, 255, 90);"
                                 "border-style: outset;"
                                 "border-width: 1px;"
                                 "border-radius: 10px;"
                                 "border-color: white;"
                                 "}");
    CB_errorright3->setStyleSheet("QPushButton {"
                                 "background-color: rgb(252, 255, 90);"
                                 "border-style: outset;"
                                 "border-width: 1px;"
                                 "border-radius: 10px;"
                                 "border-color: white;"
                                 "}");

}

void ErrorRight::display_error_frontobs()
{
    CB_errorright2->setText("OBSTACLE");
    CB_errorright2->setStyleSheet("QPushButton {"
                                  "color: black;"
                                  "background-color: rgb(165, 1, 0);"
                                  "border-style: outset;"
                                  "border-width: 1px;"
                                  "border-radius: 10px;"
                                  "border-color: black;"
                                  "}");

}

void ErrorRight::display_error_backobs()
{
    CB_errorright3->setText("OBSTACLE");
    CB_errorright3->setStyleSheet("QPushButton {"
                                  "color: black;"
                                  "background-color: rgb(165, 1, 0);"
                                  "border-style: outset;"
                                  "border-width: 1px;"
                                  "border-radius: 10px;"
                                  "border-color: black;"
                                  "}");

}
