#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller::mainWindow = new MainWindow();

    Controller::mainWindow->show();

    return a.exec();
}
