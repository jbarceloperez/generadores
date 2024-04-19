#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>

#include "model/panel.h"    // Include necessary headers for Panel, XMLFile, etc.
#include "xml/xmlparser.h"

class Controller {
private:
    XMLFile doc;
    std::vector<Panel> panelContents;
public:
    void init();
    void run(int argc, char* argv[]);

    Panel buildPanel(XMLElemento panel);
};

#endif /* CONTROLLER_H */