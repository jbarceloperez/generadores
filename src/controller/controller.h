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
protected:
    // atributos
    PanelCollection panelCol;   // conjunto de paneles creados
    GPanel* currentPanel;       // puntero a un panel de panelCol
    // Logger log;
    dbg::log mainlog;
    dbg::log hmi;
    int argc;
    int appLogLevel;            // nivel de log, el programa no mostrará logs por debajo de este
    char* argv[];
    
    Controller() = default;
    virtual ~Controller();

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
    vector<std::string> getPanelNames();

    virtual void onPbGeneratePressed(std::string outDirectory);
    virtual bool onPbWithUIPressed(std::string uiPath);
    virtual bool onPbWithoutUIPressed(std::string name);
    virtual bool onPbAssociatePressed(int button, int action);
    virtual bool onPbDeassociatePressed(int button);
    virtual void onPbSaveXmlPressed(std::string xmlPath);
    virtual int onPbLoadXmlPressed(std::string xmlPath);
    virtual void onPbAddButtonPressed(std::string name, std::string type, std::string action);
    virtual int onPbDeletePanelPressed(std::string panel);
    virtual void onPbDelButtonPressed(int button);
    virtual void changeCurrentPanel(int index);
    virtual bool onComboPanelsChanged(int index);
    virtual void onHeaderSavePressed(SaesHeader* header);
    virtual bool changeCurrentPanelSize(int h, int w);
    virtual std::string panelInfo();
};

#endif /* CONTROLLER_H */
