#include "controller.h"
#include <iostream>

#include "../model/generador.h"

#include <bits/getopt_core.h>

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
    dbg::log::initialize("/home/javi/Documentos/Generadores/traces.cfg");
    // log.log_hmi(INFO, "Starting logger...");
    // log.log_mainlog(INFO, "Starting logger...");
    hmi = dbg::log("hmi");
    mainlog = dbg::log("main");
    mainlog.info("Starting logger...");
    hmi.info("Starting logger...");

    appLogLevel = TRACE;
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

// todo: fix logger
void Controller::printTrace(TraceLevel level, string msg)
{   
    if (level >= appLogLevel)
    {
        switch (level)
        {
        case TRACE:
            mainlog.trace(msg.c_str());
            break;
        case DEBUG:
            mainlog.debug(msg.c_str());
            break;
        case INFO:
            mainlog.info(msg.c_str());
            break;
        case WARNING:
            mainlog.warning(msg.c_str());
            break;
        case ERROR:
            mainlog.error(msg.c_str());
            break;
        case CRITICAL:
            mainlog.critical(msg.c_str());
            break;
        
        default:
            break;
        }
    }  
}

GPanel* Controller::getCurrentPanel() const
{
    return currentPanel;
}

vector<string> Controller::getPanelNames() {
    return panelCol.getNames();
}

void Controller::onPbGeneratePressed() {} // a implementar en subclase
bool Controller::onPbWithUIPressed(std::string uiPath) {return 0;} // a implementar en subclase
bool Controller::onPbWithoutUIPressed(std::string name) {return 0;} // a implementar en subclase
bool Controller::onPbAssociatePressed(int button, int action) {return 0;} // a implementar en subclase
bool Controller::onPbDeassociatePressed(int button) {return 0;} // a implementar en subclase
void Controller::onPbSaveXmlPressed() {} // a implementar en subclase
int Controller::onPbLoadXmlPressed(std::string xmlPath) {return 0;} // a implementar en subclase
void Controller::onPbAddButtonPressed(std::string name, std::string type, std::string action) {} // a implementar en subclase
int Controller::onPbDeletePanelPressed(std::string panel) {return 0;} // a implementar en subclase
void Controller::onPbDelButtonPressed(int button) {} // a implementar en subclase
void Controller::changeCurrentPanel(int index) {} // a implementar en subclase
bool Controller::onComboPanelsChanged(int index) {return 0;} // a implementar en subclase
void Controller::onHeaderSavePressed(SaesHeader* header) {} // a implementar en subclase
bool Controller::changeCurrentPanelSize(int h, int w) {return 0;} // a implementar en subclase
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
        printTrace(INFO, "Same panel '" + name + "' alredy loaded. Ignoring.");
        return false;
    }
    // nuevo panel
    panelCol.addPanel(name);
    currentPanel = panelCol.getPanelByName(name);
    
    printTrace(TRACE, "Loaded panel '" + name + "'");

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
            currentPanel->addButton(QPUSHBUTTON, i.getAttributeValue("name"));
            Controller::getInstance().printTrace(WARNING, "QPushButton: " + i.getAttributeValue("name"));
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
    XMLFile doc(inputFileName.data());

    try
    {
        doc.read();
    }
    catch(const XMLFileException& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Error loading path '" << inputFileName << "'\n";
        exit(EXIT_FAILURE);
    }
    for(XMLElement panel : doc.getRootElement().getElements()) {
        panelCol.addPanel(parser.buildPanel(panel));
    }
}

/**
 * Función que genera ficheros. Primero, lee el archivo xml de entrada
 * con la configuración de los ficheros a generar. Después, para
 * cada panel en la colección, llama a la lógica del generador para
 * generar su estructura de clases.
*/
void Controller::generateAllFiles(string inputFile)
{
    XMLParser parser;
    XMLFile doc(inputFile.data());

    try
    {
        doc.read();
    }
    catch(const XMLFileException& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Error loading path '" << inputFile << "'\n";
        exit(EXIT_FAILURE);
    }
    // cerr << doc.toString();  // DEBUG
    for(XMLElement panel : doc.getRootElement().getElements()) {
        panelGen.addPanel(parser.buildPanel(panel));
    }
    for (GPanel panel : panelGen.getVector())
    {
        generatePanelFiles(panel);
        printTrace(INFO, "Ended generating files for " + panel.getName() + "\n");
    }
}