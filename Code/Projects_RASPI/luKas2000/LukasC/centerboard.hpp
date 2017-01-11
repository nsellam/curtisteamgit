#ifndef CENTERBOARD_HPP
#define CENTERBOARD_HPP

#include <QFrame>
#include <QGraphicsView>
#include "LukasC/error_left.hpp"
#include "LukasC/error_right.hpp"
#include "LukasC/us_center.hpp"
#include "Size/size.hpp"

class CenterBoard : public QFrame
{
    Q_OBJECT

    public:
    CenterBoard(QWidget *parent = 0);
    USCenter *CB_us_center;
    ErrorLeft *CB_error_left;
    ErrorRight *CB_error_right;

    public slots:

    signals:
    //signals

    private:

};

#endif // CENTERBOARD_HPP
