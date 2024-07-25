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
    Logger log;

    int argc;
    char* argv[];
    
    Controller() = default;
    virtual ~Controller();

    void iterateXML(XMLElement e);
    bool readUiXml(XMLFile ui);
    void readInputXml(string file);
    void generateAllFiles(string inputFile);
    void nogui(int _argc, char *_argv[]);

public:
    Controller(Controller const &) = delete;
    static Controller &getInstance();

    void init(int _argc, char *_argv[]);
    GPanel* getCurrentPanel() const;
    vector<std::string> getPanelNames();
    Logger* getLogger();

    virtual void onPbGeneratePressed(std::string outDirectory);
    virtual bool onPbWithUIPressed(std::string uiPath);
    virtual bool onPbWithoutUIPressed(std::string name);
    virtual bool onPbAssociatePressed(int button, int action);
    virtual bool onPbDeassociatePressed(int button);
    virtual void onPbSaveXmlPressed(std::string xmlPath);
    virtual int onPbLoadXmlPressed(std::string xmlPath);
    virtual void onPbAddButtonPressed(std::string name, std::string action);
    virtual int onPbDeletePanelPressed(std::string panel);
    virtual void onPbDelButtonPressed(int button);
    virtual void changeCurrentPanel(int index);
    virtual bool onComboPanelsChanged(int index);
    virtual void onHeaderSavePressed(SaesHeader* header);
    virtual void onHeaderSaveToAllPanelsPressed(SaesHeader* header);
    virtual bool changeCurrentPanelHeigth(int h);
    virtual bool changeCurrentPanelWidth(int w);
    virtual void changeTestGeneration(bool value);
    virtual std::string panelInfo();
};

#endif /* CONTROLLER_H */
