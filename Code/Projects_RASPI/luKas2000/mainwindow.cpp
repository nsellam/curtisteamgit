#include "mainwindow.hpp"

MainWindow::MainWindow()
{
    this->setFixedSize(SU*130, SU*39);
    mainboard = new QFrame();
    mainboard->setGeometry(SU, SU, SU*129, SU*38);
    mainboard->setStyleSheet("QFrame { background-color: rgb(30,30,30) }");

    scene = new QGraphicsScene;
    scene->setSceneRect(+SU, SU, SU*128, SU*38);

    leftboard = new LeftBoard(mainboard);
    centerboard = new CenterBoard(mainboard);
    rightboard = new RightBoard(mainboard);

    leftboard->setGeometry(SU*7, SU*4, SU*40, SU*32);
    centerboard->setGeometry(SU*47, 0, SU*33, SU*34);
    rightboard->setGeometry(SU*80, SU*4, SU*40, SU*32);

#ifdef __TEST
#ifdef __TEST_1
    maincontroller = new Test1(mainboard);
#endif //__TEST_1
#ifdef __TEST_2
    maincontroller = new Test2(mainboard);
#endif //__TEST_2
#ifdef __TEST_3
    carthread = new QThread(mainboard);
    maincontroller = new MainController(mainboard);
    maincontroller->moveToThread(carthread);
#endif //__TEST_3
#else
    maincontroller = new MainController(mainboard);
#endif //__TEST

    /* Connect */
#ifdef __TEST
    connect(rightboard->RB_start_button, SIGNAL(clicked()), maincontroller, SLOT(start())) ;
#endif //__TEST
#ifdef __TEST_1
    connect(leftboard->LB_ctrl_motorspeed, SIGNAL(valueChanged(int)), leftboard->LB_lcd_motorspeed, SLOT(display(int))) ;
#else
    connect(leftboard->LB_ctrl_motorspeed, SIGNAL(valueChanged(int)), maincontroller, SLOT(setMotorSpeed(int))) ;
    connect(maincontroller, SIGNAL(get_motorspeed(int)), leftboard->LB_lcd_motorspeed, SLOT(display(int))) ;
#endif //__TEST_1
    connect(maincontroller, SIGNAL(get_carspeed(int)), leftboard->LB_lcd_carspeed, SLOT(display(int)));
    connect(maincontroller, SIGNAL(get_carspeed(int)), leftboard, SLOT(display_carspeed(int)));
    connect(maincontroller, SIGNAL(get_kmcounter(int)), leftboard->LB_lcd_kmcounter, SLOT(display(int)));
    connect(maincontroller, SIGNAL(get_battery(int)), rightboard, SLOT(display_battery(int)));
    connect(maincontroller, SIGNAL(get_us_fl(int)), centerboard->CB_us_center, SLOT(display_us_fl(int)));
    connect(maincontroller, SIGNAL(get_us_fc(int)), centerboard->CB_us_center, SLOT(display_us_fc(int)));
    connect(maincontroller, SIGNAL(get_us_fr(int)), centerboard->CB_us_center, SLOT(display_us_fr(int)));
    connect(maincontroller, SIGNAL(get_us_bl(int)), centerboard->CB_us_center, SLOT(display_us_bl(int)));
    connect(maincontroller, SIGNAL(get_us_bc(int)), centerboard->CB_us_center, SLOT(display_us_bc(int)));
    connect(maincontroller, SIGNAL(get_us_br(int)), centerboard->CB_us_center, SLOT(display_us_br(int)));
    connect(maincontroller, SIGNAL(get_error_frontobs()), centerboard->CB_error_right, SLOT(display_error_frontobs()));
    connect(maincontroller, SIGNAL(get_error_backobs()), centerboard->CB_error_right, SLOT(display_error_backobs()));
#ifdef __TEST
#ifdef __TEST_3
    carthread->start();
#endif //__TEST_3
#else
    connect(maincontroller, SIGNAL(get_critical_battery()), centerboard->CB_error_left, SLOT(display_critical_battery()));
    maincontroller->start();
#endif //__TEST

    leftboard->setStyleSheet("QFrame {"
                             "border: 2px solid white;"
                             "padding: 2px;"
                             "background-color: rgb(0, 0, 0);"
                             "}");
    rightboard->setStyleSheet("QFrame {"
                             "border: 2px solid white;"
                             "padding: 2px;"
                             "background-color: rgb(0, 0, 0);"
                             "}");

    mainboard_widget = scene->addWidget(mainboard);

    view = new QGraphicsView();
    view->setScene(scene);
    this->setCentralWidget(view);
}
