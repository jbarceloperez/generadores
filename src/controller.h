#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "model/panel.h"    // Include necessary headers for Panel, XMLFile, etc.
#include "xml/xmlparser.h"
#include "model/panelbuilder.h"
#include "logs.hpp"

enum DebugLevel {
    TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL
};

class Controller {
private:
    XMLFile doc;
    // std::vector<PanelBuilder> panelBuilders;
    std::vector<Panel> panelContents;
    Panel currentPanel;
    dbg::log mainlog;
    dbg::log tracks;
    int argc;
    int appLogLevel;
    char* argv[];
    
    Controller() {};

public:
    Controller(Controller const&) = delete;
    static Controller& getInstance();

    void init(int _argc, char* _argv[]);
    void run();
    void printTrace(DebugLevel level, string msg);

    void onPbGeneratePressed();
    void onPbWithUIPressed(string uiPath);
    void onPbWithoutUIPressed();
    void onPbFilePressed(string file);
    void updateUi();

    void iterateXML(XMLElemento e);
    void readUiXml(XMLFile ui);
    Panel buildPanel(XMLElemento panel);

    
};

#endif /* CONTROLLER_H */
