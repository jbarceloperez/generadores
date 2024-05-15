#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>

#include "model/panelcollection.h"
#include "model/panel.h"
#include "xml/xmlparser.h"
#include "logs.hpp"

enum DebugLevel {
    TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL
};

class Controller {
private:
    // atributos

    PanelCollection panelCol; // conjunto de paneles creados
    GPanel* currentPanel;     // puntero a un panel de panelCol
    dbg::log mainlog;
    dbg::log tracks;
    int argc;
    int appLogLevel;
    char* argv[];
    
    Controller() {};

    void iterateXML(XMLElemento e);
    bool readUiXml(XMLFile ui);
    GPanel buildPanel(XMLElemento panel);
    void readInputXml(string file);
    void generateAllFiles(string inputFile);

public:
    Controller(Controller const &) = delete;
    static Controller &getInstance();

    void init(int _argc, char* _argv[]);
    void printTrace(DebugLevel level, string msg);
    GPanel* getCurrentPanel() const;
    vector<string> getPanelNames();

    void onPbGeneratePressed();
    bool onPbWithUIPressed(string uiPath);
    bool onPbWithoutUIPressed(string name);
    bool onPbAssociatePressed(int button, int action);
    bool onPbDeassociatePressed(int button);
    void onPbSaveXmlPressed();
    int onPbLoadXmlPressed(string xmlPath);
    void onPbAddButtonPressed(string name, string type, string action);
    int onPbDeletePanelPressed(string panel);
    void onPbDelButtonPressed(int button);
    void changeCurrentPanel(int index);
    string panelInfo();
};

#endif /* CONTROLLER_H */
