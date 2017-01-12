#include "LukasC/centerboard.hpp"

CenterBoard::CenterBoard(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    CB_error_left = new ErrorLeft(this);
    CB_error_right = new ErrorRight(this);
    CB_us_center = new USCenter(this);

    CB_error_left->setGeometry(0, SU*4, SU*10, SU*30);
    CB_us_center->setGeometry(SU*10, 0, SU*13, SU*34);
    CB_error_right->setGeometry(SU*23, SU*4, SU*10, SU*30);

    CB_error_left->setStyleSheet("QFrame {"
                                 "border: 2px solid white;"
                                 "padding: 2px;"
                                 "background-color: rgb(0, 0, 0);"
                                 "}");
    CB_error_right->setStyleSheet("QFrame {"
                                  "border: 2px solid white;"
                                  "padding: 2px;"
                                  "background-color: rgb(0, 0, 0);"
                                  "}");
    CB_us_center->setStyleSheet("QFrame {"
                                "border: 2px solid white;"
                                "padding: 2px;"
                                "background-color: rgb(0, 0, 0);"
                                "}");

}
