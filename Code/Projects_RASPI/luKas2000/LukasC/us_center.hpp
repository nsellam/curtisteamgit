#ifndef US_CENTER_HPP
#define US_CENTER_HPP

#include <QFrame>
#include <QGraphicsView>
#include <QProgressBar>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QLabel>
#include "Size/size.hpp"

class USCenter : public QFrame
{
    Q_OBJECT

    public:
    USCenter(QWidget *parent = 0);

    public slots:
    void display_us_fl(int value);
    void display_us_fc(int value);
    void display_us_fr(int value);
    void display_us_bl(int value);
    void display_us_bc(int value);
    void display_us_br(int value);

    signals:
    //signals

    private:
    QFrame *CB_us_car;
    QLabel *CB_us_car_img;
    QProgressBar *CB_us_frontleft;
    QProgressBar *CB_us_frontcenter;
    QProgressBar *CB_us_frontright;
    QProgressBar *CB_us_backleft;
    QProgressBar *CB_us_backcenter;
    QProgressBar *CB_us_backright;

};

#endif // US_CENTER_HPP
