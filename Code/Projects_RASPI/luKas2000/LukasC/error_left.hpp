#ifndef ERROR_LEFT_CPP
#define ERROR_LEFT_CPP

#include <QFrame>
#include <QGraphicsView>
#include <QPushButton>
#include <QFont>
#include "Size/size.hpp"

class ErrorLeft : public QFrame
{
    Q_OBJECT

    public:
    ErrorLeft(QWidget *parent = 0);

    public slots:
    void display_critical_battery();

    signals:
    //signals

    private:
    QPushButton *CB_errorleft1;
    QPushButton *CB_errorleft2;
    QPushButton *CB_errorleft3;

};

#endif // ERROR_LEFT_CPP
