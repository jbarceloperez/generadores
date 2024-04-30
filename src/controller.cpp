#include "controller.h"
#include <iostream>
#include <string>

#include "model/panelbuilder.h"
#include "model/generador.h"


Controller& Controller::getInstance() {
    static Controller instance;
    return instance;
}

void Controller::init(int _argc, char *_argv[])
{
    argc = _argc;
    for (int i = 0; i < argc; i++)
    {
        argv[i] = _argv[i];
    }
    // dbg::log::initialize("../traces.cfg");
    dbg::log::initialize("/home/javi/Documentos/Generadores/src/traces.cfg");
    appLogLevel = INFO;
    currentPanel = GPanel("");
}


void Controller::printTrace(DebugLevel level, string msg)
{   
    if (level >= appLogLevel)
    {
        switch (level)
        {
        case TRACE:
            mainlog.warning(msg.c_str());
            break;
        case DEBUG:
            mainlog.warning(msg.c_str());
            break;
        case INFO:
            mainlog.warning(msg.c_str());
            break;
        case WARNING:
            mainlog.warning(msg.c_str());
            break;
        case ERROR:
            mainlog.warning(msg.c_str());
            break;
        case CRITICAL:
            mainlog.warning(msg.c_str());
            break;
        
        default:
            break;
        }
    }
    // mainlog.warning(msg.c_str());
    
}

void Controller::onPbGeneratePressed()
{

}

bool Controller::onPbWithUIPressed(string uiPath)
{        
    XMLFile uiXml;
    try
    {
        uiXml = XMLFile(uiPath.data());
    }   // TODO: Manejar el error en vez de excepción
    catch(const XMLFileException& e)
    {
        printTrace(CRITICAL, e.what());
        printTrace(CRITICAL, "Error loading path '" + uiPath + "'\n");
    }
    if (readUiXml(uiXml))
    {
        panelContents.push_back(currentPanel);
        return true;
    }
    return false;    
}

void Controller::onPbWithoutUIPressed()
{

}

void Controller::onPbFilePressed(string file)
{

}

GPanel Controller::getCurrentPanel() const
{
    return currentPanel;
}

void Controller::run()
{
    
    // Logger
    tracks.info("Code generator saes initializing...\n");
    mainlog.info("Traza warning\n");
    mainlog.critical("starting generating...\n");
    char* inputFileName = argv[1];

    /* TODO:Detectar si la entrada es un .ui o un .xml, para poder
            directamente leer el ui y generar la estructura de clases
            a partir de este, o hace falta generar también el ui
    */
   // regex pattern("\\.ui$");
   // regex_search(string(inputFileName), pattern);

    // XML PARSER
    
    
    try
    {
        doc = XMLFile(inputFileName);
    }
    catch(const XMLFileException& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Error loading path '" << inputFileName << "'\n";
        exit(EXIT_FAILURE);
    }
    catch(const XMLParseException& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Missing <panels> element in XML file." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    

    // Aquí comienza a detectar paneles a generar

    for(XMLElemento panel : doc.getRootElement().getElementos()) {
        panelContents.push_back(buildPanel(panel));
    }


    // a este punto ya debería tener los paneles claros, ahora toca
    // decidir cómo los va a generar cada uno, en su subcarpeta y con
    // sus características

    for(GPanel panel : panelContents)
    {
        // std::cout << panel.toString() << std::endl; // DEBUG

        generateFiles(panel);

        cout << "Ended generating files for " + panel.getName() + "\n\n";
    }
}

GPanel Controller::buildPanel(XMLElemento panel)
{
    // elementos obligatorios
    string type = panel.getAtributoValue("type");
    string name = panel.getAtributoValue("name");

    GPanel panelObject = GPanel(name);
    panelObject.setType(type);

    // otros elementos
    for (XMLElemento e : panel.getElementos()) {
        // TRATAR CADA POSIBLE ELEMENTO QUE SE QUIERA CONTEMPLAR

        // TODO: HACER UN SWITCH-CASE CON UN ENUM DE DIFERENTES
        // TIPOS DE ELEMENTO XML PARA LA APLICACION

        string name = e.getName();
        if (!name.compare("geometry")) {
            try
            {
                panelObject.setWidth(atoi(e.getSubelement("w").getContent().c_str()));
                panelObject.setHeight(atoi(e.getSubelement("h").getContent().c_str()));
            }
            catch(const XMLElementNotFoundException e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }

    return panelObject;
}


bool Controller::readUiXml(XMLFile ui)
{
    // std::cerr << ui.toString();      // DEBUG

    XMLElemento root = ui.getRootElement();
    // get the name
    std::string name = root.getSubelement("class").getContent();
    if (!currentPanel.getName().compare(name))
    {
        printTrace(INFO, "Same panel '" + name + "' loaded. Ignoring.");
        return false;
    }
    printTrace(TRACE, "Loaded panel '" + name + "'");
    currentPanel.setName(name);
    
    iterateXML(root);
    
    if (!currentPanel.getButtons().size()) {
        currentPanel.setType(PanelType::EXTERNAL_UI_READ);
    }
    else {
        currentPanel.setType(PanelType::EXTERNAL_UI_CONFIG);
    }
    return true;
}

void Controller::iterateXML(XMLElemento e)
{
    vector<XMLElemento> subelementos = e.getElementos();
    for (XMLElemento i : subelementos)
    {
        string aux = i.getAtributoValue("class");
        if (!aux.compare("QPushButton"))
        {
            currentPanel.addButton(QPUSHBUTTON, i.getAtributoValue("name"));
            Controller::getInstance().printTrace(WARNING, "QPushButton: " + i.getAtributoValue("name"));
        }
        
        iterateXML(i);
        
    }
}
