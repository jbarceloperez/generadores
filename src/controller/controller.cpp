#include "controller.h"
#include <iostream>
#include "../model/generador.h"
#include <bits/getopt_core.h>

#define TRACES_CONFIG_PATH "/home/javi/Documentos/Generadores/traces.cfg"


Controller::~Controller() {}

// implementación del singleton
Controller& Controller::getInstance() {
    static Controller instance;
    return instance;
}

// inicializa el controlador
void Controller::init(int _argc, char *_argv[])
{
    argc = _argc;
    for (int i = 0; i < argc; i++)
    {
        argv[i] = _argv[i];
    }
    panelCol.init();
    log = Logger();
    log.init(TRACES_CONFIG_PATH);
    log.hmilog(INFO, "Initializing logger...");
    log.mainlog(INFO, "Initializing logger...");
    currentPanel = nullptr;
    nogui(_argc, _argv);
}

void Controller::nogui(int _argc, char *_argv[])
{
    int c;
    char *path;
    int nogui = 0; // flag
    while ((c = getopt(_argc, _argv, "hn:")) != -1)
    {
        switch (c)
        {
        case 'n':
            nogui = 1;
            path = optarg;
            break;
        case 'h':
            cout << "codeGenerator [-n NO GUI MODE] input.xml\n";
            exit(EXIT_FAILURE);
            break;
        default:
            break;
        }
    }
    if (nogui) // ejecución nogui
    {
        cout << "   - codeGenerator - no gui mode -\n\n";
        generateAllFiles(path);
        exit(EXIT_SUCCESS);
    }
}

GPanel* Controller::getCurrentPanel() const
{
    return currentPanel;
}

vector<string> Controller::getPanelNames() {
    return panelCol.getNames();
}

Logger *Controller::getLogger()
{
    return &log;
}

void Controller::onPbGeneratePressed(std::string outDirectory) {} // a implementar en subclase
bool Controller::onPbWithUIPressed(std::string uiPath) {return 0;} // a implementar en subclase
bool Controller::onPbWithoutUIPressed(std::string name) {return 0;} // a implementar en subclase
bool Controller::onPbAssociatePressed(int button, int action) {return 0;} // a implementar en subclase
bool Controller::onPbDeassociatePressed(int button) {return 0;} // a implementar en subclase
void Controller::onPbSaveXmlPressed(std::string xmlPath) {} // a implementar en subclase
int Controller::onPbLoadXmlPressed(std::string xmlPath) {return 0;} // a implementar en subclase
void Controller::onPbAddButtonPressed(std::string name, std::string action) {} // a implementar en subclase
int Controller::onPbDeletePanelPressed(std::string panel) {return 0;} // a implementar en subclase
void Controller::onPbDelButtonPressed(int button) {} // a implementar en subclase
void Controller::changeCurrentPanel(int index) {} // a implementar en subclase
bool Controller::onComboPanelsChanged(int index) {return 0;} // a implementar en subclase
void Controller::onHeaderSavePressed(SaesHeader* header) {} // a implementar en subclase
void Controller::onHeaderSaveToAllPanelsPressed(SaesHeader *header) {} // a implementar en subclase
bool Controller::changeCurrentPanelHeigth(int h) { return 0; } // a implementar en subclase
bool Controller::changeCurrentPanelWidth(int w) {return 0;} // a implementar en subclase
string Controller::panelInfo() {return "";} // a implementar en subclase

//-------------------------------------------------------------------
//-------------------------------------------------------------------

/**
 * Lee el archivo XML con la ui del panel a crear, y crea y añade a la
 * colección dicho panel con las propiedades detectadas en el .ui
*/
bool Controller::readUiXml(XMLFile ui)
{
    XMLElement root = ui.getRootElement();
    // get the name
    std::string name = root.getSubelement("class").getContent();
    if (panelCol.containsPanel(name))
    {
        log.mainlog(INFO, "Same panel '" + name + "' alredy loaded. Ignoring.");
        return false;
    }
    // nuevo panel
    panelCol.addPanel(name);
    currentPanel = panelCol.getPanelByName(name);
    
    log.mainlog(TRACE, "Loaded panel '" + name + "'");

    currentPanel->setUiPath(ui.getXmlPath());
    currentPanel->setLayout(EXTERNAL_UI);       // no hay ui, no hay layout
    iterateXML(root);
    if (!currentPanel->getButtons().size()) {
        currentPanel->setType(PanelType::EXTERNAL_UI_READ);
    }
    else {
        currentPanel->setType(PanelType::EXTERNAL_UI_CONFIG);
    }
    return true;
}

/**
 * Hace un recorrido primero en profundidad el XML, buscando elementos
 * botón y añadiéndolos al objeto panel.
*/
void Controller::iterateXML(XMLElement e)
{
    vector<XMLElement> subelementos = e.getElements();
    for (XMLElement i : subelementos)
    {
        string aux = i.getAttributeValue("class");
        if (aux == "QPushButton")
        {
            currentPanel->addButton(i.getAttributeValue("name"));
            log.mainlog(WARNING, "QPushButton: " + i.getAttributeValue("name"));
        }
        iterateXML(i);
    }
}

/**
 * Dado el nombre de un archivo de entrada que es un XML de entrada
 * del generador, lee el documento XML y por cada elemento panel va
 * generando un elemento y añadiendolo a la colección de paneles.
*/
void Controller::readInputXml(string inputFileName)
{
    XMLParser parser;
    XMLFile doc = parser.readXml(inputFileName.data());
    for(XMLElement panel : doc.getRootElement().getElements()) {
        panelCol.addPanel(parser.buildPanel(panel));
    }
}

/**
 * Función que genera ficheros. Para cada panel en la colección 
 * de paneles, llama a la lógica del generador para generar su 
 * estructura de clases en el directorio pasado como parámetro.
*/
void Controller::generateAllFiles(string outDirectory)
{
    Generador g;
    for (GPanel panel : panelCol.getVector())
    {
        g.generatePanelFiles(panel, outDirectory);
        log.mainlog(INFO, "Ended generating files for " + panel.getName() + "\n");
    }
}