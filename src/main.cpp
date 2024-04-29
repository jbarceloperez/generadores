#include <QApplication>
#include "gui/MainPanel.h"
#include "controller.h"


int main(int argc, char* argv[]) 
{
    Controller::getInstance().init(argc, argv);
    QApplication a(argc, argv);
    MainPanel w;
    w.show();

    return a.exec();

}
