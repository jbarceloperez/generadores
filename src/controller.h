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
    std::vector<GPanel> panelContents;
    GPanel currentPanel;
    dbg::log mainlog;
    dbg::log tracks;
    int argc;
    int appLogLevel;
    char* argv[];
    
    Controller() {};

    void iterateXML(XMLElemento e);
    bool readUiXml(XMLFile ui);
    GPanel buildPanel(XMLElemento panel);

public:
    Controller(Controller const&) = delete;
    static Controller& getInstance();

    void init(int _argc, char* _argv[]);
    void run();
    void printTrace(DebugLevel level, string msg);

    void onPbGeneratePressed();
    bool onPbWithUIPressed(string uiPath);
    void onPbWithoutUIPressed();
    void onPbFilePressed(string file);
    bool onPbAssociatePressed(int button, int action);
    void onPbDeassociatePressed();

    GPanel getCurrentPanel() const;
    

    
};

#endif /* CONTROLLER_H */
