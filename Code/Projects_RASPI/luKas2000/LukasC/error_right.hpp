#ifndef ERROR_RIGHT_HPP
#define ERROR_RIGHT_HPP

#include <QFrame>
#include <QGraphicsView>
#include <QPushButton>
#include <QFont>
#include "Size/size.hpp"

class ErrorRight : public QFrame
{
    Q_OBJECT

    public:
    ErrorRight(QWidget *parent = 0);

    public slots:
    void display_error_frontobs();
    void display_error_backobs();

    signals:
    //signals

    private:
    QPushButton *CB_errorright1;
    QPushButton *CB_errorright2;
    QPushButton *CB_errorright3;

};

#endif // ERROR_RIGHT_HPP
