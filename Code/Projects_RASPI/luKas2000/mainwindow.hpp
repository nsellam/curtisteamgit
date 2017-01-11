#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

//#define __TEST
//#define __TEST_3

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include "LukasL/leftboard.hpp"
#include "LukasC/centerboard.hpp"
#include "LukasR/rightboard.hpp"
#ifdef __TEST
#ifdef __TEST_1
#include "Tests/test_1.hpp"
#endif //__TEST_1
#ifdef __TEST_2
#include "Tests/test_2.hpp"
#endif //__TEST_2
#ifdef __TEST_3
#include "Tests/test_3.hpp"
#endif //__TEST_3
#else
#include "maincontroller.hpp"
#endif //__TEST

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();

    public slots:

    signals:
    //signals

    private:
    QFrame *mainboard;
    LeftBoard *leftboard;
    CenterBoard *centerboard;
    RightBoard * rightboard;
    QGraphicsProxyWidget *mainboard_widget;
    QGraphicsScene *scene;
    QGraphicsView *view;
#ifdef __TEST
#ifdef __TEST_1
    Test1 *maincontroller;
#endif //__TEST_1
#ifdef __TEST_2
    Test2 *maincontroller;
#endif //__TEST_2
#ifdef __TEST_3
    QThread *carthread;
    Test3 *maincontroller;
#endif //__TEST_3
#else
    MainController *maincontroller;
#endif //__TEST



};

#endif // MAINWINDOW_HPP
