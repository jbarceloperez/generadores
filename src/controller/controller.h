#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>

#include "../model/panelcollection.h"
#include "../model/gpanel.h"
#include "../model/saesheader.h"
#include "../xml/xmlelement.h"
#include "../xml/xmlfile.h"
#include "../xml/xmlexception.h"
#include "../xml/xmlparser.h"
#include "../log/logger.h"

class Controller {
private:
    // atributos
    PanelCollection panelCol;   // conjunto de paneles creados
    PanelCollection panelGen;   // conjunto de paneles leidos del XML, para generarlos
    GPanel* currentPanel;       // puntero a un panel de panelCol
    // Logger log;
    dbg::log mainlog;
    dbg::log hmi;
    int argc;
    int appLogLevel;            // nivel de log, el programa no mostrará logs por debajo de este
    char* argv[];
    
    Controller() {};

    void iterateXML(XMLElement e);
    bool readUiXml(XMLFile ui);
    void readInputXml(string file);
    void generateAllFiles(string inputFile);

public:
    Controller(Controller const &) = delete;
    static Controller &getInstance();

    void init(int _argc, char *_argv[]);
    void nogui(int _argc, char *_argv[]);
    void printTrace(TraceLevel trace, string msg);
    Logger *getAppLogger();
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
    bool onComboPanelsChanged(int index);
    void onHeaderSavePressed(SaesHeader* header);
    bool changeCurrentPanelSize(int h, int w);
    string panelInfo();
};

#endif /* CONTROLLER_H */
