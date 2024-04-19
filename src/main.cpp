// #include <iostream>
#include <QApplication>
#include "gui/MainPanel.h"
#include "controller.h"


int main(int argc, char* argv[]) 
{
    Controller c;
    // std::cout << "PROBANDO\n";      // debug
    // c.run(argc, argv);
    // return EXIT_SUCCESS;

    QApplication a(argc, argv);
    MainPanel w;
    w.show();

    return a.exec();

}
