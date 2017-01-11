#include <QApplication>
#include <QFile>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Lukas2000");

    MainWindow dashboard; //créer une fenêtre

    dashboard.show(); //à la fin, afficher la fenêtre

    return app.exec();
}
