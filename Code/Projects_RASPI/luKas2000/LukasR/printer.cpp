#include "LukasR/printer.hpp"

Printer::Printer(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    this->setStyleSheet("QFrame {"
                        "background-color: rgb(38, 155, 185);"
                        "color: white;"
                        "border: 2px solid white;"
                        "padding: 2px;"
                        "border-radius: 5px;"
                        "}");

    //printer_view = new QGraphicsView;
    //printer_view->setGeometry(0, 0, 152, 104);

}
