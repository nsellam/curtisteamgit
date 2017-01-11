#include "LukasR/rightboard.hpp"

RightBoard::RightBoard(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    RB_camera = new Camera(this);
    RB_camera->setGeometry(SU*19, SU*2, SU*19, SU*13);

    RB_printer = new Printer(this);
    RB_printer->setGeometry(SU*19, SU*17, SU*19, SU*13);

    RB_battery = new QProgressBar(this);
    RB_battery->setGeometry(SU, SU*26, SU*14, SU*2);
    RB_battery->setValue(0);
    RB_battery->setTextVisible(false);

    //RB_start_button = new QPushButton("START", this);
    //RB_start_button->setGeometry(SU*5, SU*5, SU*5, SU*5);

    RB_battery->setStyleSheet("QProgressBar:horizontal {"
                              "border: 1px solid white;"
                              "background: black;"
                              "border-radius: 2px;"
                              "padding: 1px;"
                              "}"
                              "QProgressBar::chunk:horizontal {"
                              "background: green;"
                              "margin-right: 2px; /* space */"
                              "width: 3px;"
                              "}");

}

void RightBoard::display_battery(int value)
{
    RB_battery->setValue(value);
    if (value <= 60)
    {
        RB_battery->setStyleSheet("QProgressBar:horizontal {"
                                  "border: 1px solid white;"
                                  "background: black;"
                                  "border-radius: 2px;"
                                  "padding: 1px;"
                                  "}"
                                  "QProgressBar::chunk:horizontal {"
                                  "background: rgb(252, 255, 90);"
                                  "margin-right: 2px; /* space */"
                                  "width: 3px;"
                                  "}");
        }
    else {
        if (value <= 20)
        {
            RB_battery->setStyleSheet("QProgressBar:horizontal {"
                                  "border: 1px solid white;"
                                  "background: black;"
                                  "border-radius: 2px;"
                                  "padding: 1px;"
                                  "}"
                                  "QProgressBar::chunk:horizontal {"
                                  "background: rgb(165, 1, 0);"
                                  "margin-right: 2px; /* space */"
                                  "width: 3px;"
                                  "}");
        } else {
            RB_battery->setStyleSheet("QProgressBar:horizontal {"
                                  "border: 1px solid white;"
                                  "background: black;"
                                  "border-radius: 2px;"
                                  "padding: 1px;"
                                  "}"
                                  "QProgressBar::chunk:horizontal {"
                                  "background: green;"
                                  "margin-right: 2px; /* space */"
                                  "width: 3px;"
                                  "}");
        }
    }
}
