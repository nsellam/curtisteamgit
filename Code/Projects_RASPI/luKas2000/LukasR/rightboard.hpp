#ifndef RIGHTBOARD_HPP
#define RIGHTBOARD_HPP

#include <QFrame>
#include <QGraphicsView>
#include <QProgressBar>
#include <QPushButton>
#include "LukasR/camera.hpp"
#include "LukasR/printer.hpp"
#include "Size/size.hpp"

class RightBoard : public QFrame
{
    Q_OBJECT

    public:
    RightBoard(QWidget *parent = 0);
    QProgressBar *RB_battery;
    QPushButton *RB_start_button;

    public slots:
    void display_battery(int value);

    signals:

    private:
    Camera *RB_camera;
    Printer *RB_printer;

};

#endif // RIGHTBOARD_HPP
