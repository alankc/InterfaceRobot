#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mymap.h"
#include "mainwindow.h"

class Controller
{
public:
    Controller();
    static MainWindow *mainWindow;
    static MyMap myMap;
};

#endif // CONTROLLER_H
