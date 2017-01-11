#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <QFrame>
#include <QGraphicsView>

class Printer : public QFrame
{
    Q_OBJECT

    public:
    Printer(QWidget *parent = 0);

    public slots:

    signals:
    //signals

    private:
    QGraphicsView *printer_view;

};

#endif // PRINTER_HPP
