#include <QApplication>
#include "gui/GeneratorPanelImpl.h"
#include "controller.h"


int main(int argc, char* argv[]) 
{
    Controller::getInstance().init(argc, argv);
    QApplication a(argc, argv);
    GeneratorPanelImpl w;
    w.show();

    return a.exec();

}
