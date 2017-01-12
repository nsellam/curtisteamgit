#include "LukasC/us_center.hpp"

USCenter::USCenter(QWidget *parent) : QFrame(parent)
{
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);

    CB_us_frontleft = new QProgressBar(this);
    CB_us_frontleft->setGeometry(SU, SU, SU*3, SU*8);
    CB_us_frontleft->setValue(0);
    CB_us_frontleft->setTextVisible(false);
    CB_us_frontleft->setOrientation(Qt::Vertical);

    CB_us_frontcenter = new QProgressBar(this);
    CB_us_frontcenter->setGeometry(SU*5, SU, SU*3, SU*8);
    CB_us_frontcenter->setValue(0);
    CB_us_frontcenter->setTextVisible(false);
    CB_us_frontcenter->setOrientation(Qt::Vertical);

    CB_us_frontright = new QProgressBar(this);
    CB_us_frontright->setGeometry(SU*9, SU, SU*3, SU*8);
    CB_us_frontright->setValue(0);
    CB_us_frontright->setTextVisible(false);
    CB_us_frontright->setOrientation(Qt::Vertical);

    CB_us_backleft = new QProgressBar(this);
    CB_us_backleft->setGeometry(SU, SU*25, SU*3, SU*8);
    CB_us_backleft->setValue(0);
    CB_us_backleft->setTextVisible(false);
    CB_us_backleft->setOrientation(Qt::Vertical);
    CB_us_backleft->setInvertedAppearance(true);

    CB_us_backcenter = new QProgressBar(this);
    CB_us_backcenter->setGeometry(SU*5, SU*25, SU*3, SU*8);
    CB_us_backcenter->setValue(0);
    CB_us_backcenter->setTextVisible(false);
    CB_us_backcenter->setOrientation(Qt::Vertical);
    CB_us_backcenter->setInvertedAppearance(true);

    CB_us_backright = new QProgressBar(this);
    CB_us_backright->setGeometry(SU*9, SU*25, SU*3, SU*8);
    CB_us_backright->setValue(0);
    CB_us_backright->setTextVisible(false);
    CB_us_backright->setOrientation(Qt::Vertical);
    CB_us_backright->setInvertedAppearance(true);

    CB_us_car = new QFrame(this);
    CB_us_car->setGeometry(SU*2, SU*10, SU*9, SU*14);
    CB_us_car->setStyleSheet("QFrame {"
                             "border: 2px solid white;"
                             "border-radius: 4px;"
                             "padding: 2px;"
                             "}");

    QPixmap car_black(":/img/car_black.png");
    CB_us_car_img = new QLabel(CB_us_car);
    CB_us_car_img->setPixmap(car_black);

    CB_us_frontleft->setStyleSheet("QProgressBar:vertical {"
                                   "border: 1px solid white;"
                                   "background: black;"
                                   "border-radius: 2px;"
                                   "padding: 1px;"
                                   "}"
                                   "QProgressBar::chunk:vertical {"
                                   "background: green;"
                                   "margin-top: 2px; /* space */"
                                   "height: 3px;"
                                   "}");
    CB_us_frontcenter->setStyleSheet("QProgressBar:vertical {"
                                   "border: 1px solid white;"
                                   "background: black;"
                                   "border-radius: 2px;"
                                   "padding: 1px;"
                                   "}"
                                   "QProgressBar::chunk:vertical {"
                                   "background: green;"
                                   "margin-top: 2px; /* space */"
                                   "height: 3px;"
                                   "}");
    CB_us_frontright->setStyleSheet("QProgressBar:vertical {"
                                   "border: 1px solid white;"
                                   "background: black;"
                                   "border-radius: 2px;"
                                   "padding: 1px;"
                                   "}"
                                   "QProgressBar::chunk:vertical {"
                                   "background: green;"
                                   "margin-top: 2px; /* space */"
                                   "height: 3px;"
                                   "}");
    CB_us_backleft->setStyleSheet("QProgressBar:vertical {"
                                   "border: 1px solid white;"
                                   "background: black;"
                                   "border-radius: 2px;"
                                   "padding: 1px;"
                                   "}"
                                   "QProgressBar::chunk:vertical {"
                                   "background: green;"
                                   "margin-bottom: 2px; /* space */"
                                   "height: 3px;"
                                   "}");
    CB_us_backcenter->setStyleSheet("QProgressBar:vertical {"
                                   "border: 1px solid white;"
                                   "background: black;"
                                   "border-radius: 2px;"
                                   "padding: 1px;"
                                   "}"
                                   "QProgressBar::chunk:vertical {"
                                   "background: green;"
                                   "margin-bottom: 2px; /* space */"
                                   "height: 3px;"
                                   "}");
    CB_us_backright->setStyleSheet("QProgressBar:vertical {"
                                   "border: 1px solid white;"
                                   "background: black;"
                                   "border-radius: 2px;"
                                   "padding: 1px;"
                                   "}"
                                   "QProgressBar::chunk:vertical {"
                                   "background: green;"
                                   "margin-bottom: 2px; /* space */"
                                   "height: 3px;"
                                   "}");

/*
    CB_us_car_item = new QGraphicsItemGroup(parent);
    CB_us_car_img = new QGraphicsPixmapItem;
    CB_us_car_img->setPixmap(QPixmap(":/img/car_black.png"));
    CB_us_car_img->setPos(16, 80);
*/
}

void USCenter::display_us_fl(int value)
{
    CB_us_frontleft->setValue(value);
    if(value <= 20)
    {
        CB_us_frontleft->setStyleSheet("QProgressBar:vertical {"
                                       "border: 1px solid white;"
                                       "background: black;"
                                       "border-radius: 2px;"
                                       "padding: 1px;"
                                       "}"
                                       "QProgressBar::chunk:vertical {"
                                       "background: rgb(165, 1, 0);"
                                       "margin-top: 2px; /* space */"
                                       "height: 3px;"
                                       "}");
    }
    else {
        if(value <= 60)
        {
            CB_us_frontleft->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: rgb(252, 255, 90);"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
        else {
            CB_us_frontleft->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: green;"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
    }
}

void USCenter::display_us_fc(int value)
{
    CB_us_frontcenter->setValue(value);
    if(value <= 20)
    {
        CB_us_frontcenter->setStyleSheet("QProgressBar:vertical {"
                                       "border: 1px solid white;"
                                       "background: black;"
                                       "border-radius: 2px;"
                                       "padding: 1px;"
                                       "}"
                                       "QProgressBar::chunk:vertical {"
                                       "background: rgb(165, 1, 0);"
                                       "margin-top: 2px; /* space */"
                                       "height: 3px;"
                                       "}");
    }
    else {
        if(value <= 60)
        {
            CB_us_frontcenter->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: rgb(252, 255, 90);"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
        else {
            CB_us_frontcenter->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: green;"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
    }
}

void USCenter::display_us_fr(int value)
{
    CB_us_frontright->setValue(value);
    if(value <= 20)
    {
        CB_us_frontright->setStyleSheet("QProgressBar:vertical {"
                                       "border: 1px solid white;"
                                       "background: black;"
                                       "border-radius: 2px;"
                                       "padding: 1px;"
                                       "}"
                                       "QProgressBar::chunk:vertical {"
                                       "background: rgb(165, 1, 0);"
                                       "margin-top: 2px; /* space */"
                                       "height: 3px;"
                                       "}");
    }
    else {
        if(value <= 60)
        {
            CB_us_frontright->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: rgb(252, 255, 90);"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
        else {
            CB_us_frontright->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: green;"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
    }
}

void USCenter::display_us_bl(int value)
{
    CB_us_backleft->setValue(value);
    if(value <= 20)
    {
        CB_us_backleft->setStyleSheet("QProgressBar:vertical {"
                                       "border: 1px solid white;"
                                       "background: black;"
                                       "border-radius: 2px;"
                                       "padding: 1px;"
                                       "}"
                                       "QProgressBar::chunk:vertical {"
                                       "background: rgb(165, 1, 0);"
                                       "margin-top: 2px; /* space */"
                                       "height: 3px;"
                                       "}");
    }
    else {
        if(value <= 60)
        {
            CB_us_backleft->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: rgb(252, 255, 90);"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
        else {
            CB_us_backleft->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: green;"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
    }
}

void USCenter::display_us_bc(int value)
{
    CB_us_backcenter->setValue(value);
    if(value <= 20)
    {
        CB_us_backcenter->setStyleSheet("QProgressBar:vertical {"
                                       "border: 1px solid white;"
                                       "background: black;"
                                       "border-radius: 2px;"
                                       "padding: 1px;"
                                       "}"
                                       "QProgressBar::chunk:vertical {"
                                       "background: rgb(165, 1, 0);"
                                       "margin-top: 2px; /* space */"
                                       "height: 3px;"
                                       "}");
    }
    else {
        if(value <= 60)
        {
            CB_us_backcenter->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: rgb(252, 255, 90);"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
        else {
            CB_us_backcenter->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: green;"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
    }
}

void USCenter::display_us_br(int value)
{
    CB_us_backright->setValue(value);
    if(value <= 20)
    {
        CB_us_backright->setStyleSheet("QProgressBar:vertical {"
                                       "border: 1px solid white;"
                                       "background: black;"
                                       "border-radius: 2px;"
                                       "padding: 1px;"
                                       "}"
                                       "QProgressBar::chunk:vertical {"
                                       "background: rgb(165, 1, 0);"
                                       "margin-top: 2px; /* space */"
                                       "height: 3px;"
                                       "}");
    }
    else {
        if(value <= 60)
        {
            CB_us_backright->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: rgb(252, 255, 90);"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
        else {
            CB_us_backright->setStyleSheet("QProgressBar:vertical {"
                                           "border: 1px solid white;"
                                           "background: black;"
                                           "border-radius: 2px;"
                                           "padding: 1px;"
                                           "}"
                                           "QProgressBar::chunk:vertical {"
                                           "background: green;"
                                           "margin-top: 2px; /* space */"
                                           "height: 3px;"
                                           "}");
        }
    }
}

