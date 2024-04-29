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
    appLogLevel = TRACE;
}


void Controller::printTrace(DebugLevel level, string msg)
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
    // mainlog.warning(msg.c_str());
    
}

void Controller::onPbGeneratePressed()
{

}

void Controller::onPbWithUIPressed(string uiPath)
{
    currentPanel = Panel("");
    XMLFile uiXml;
    try
    {
        uiXml = XMLFile(uiPath.data());
        readUiXml(uiXml);
    }
    catch(const XMLFileException& e)
    {
        printTrace(CRITICAL, e.what());
        printTrace(CRITICAL, "Error loading path '" + uiPath + "'\n");
        
    }
    panelContents.push_back(currentPanel);
}

void Controller::onPbWithoutUIPressed()
{

}

void Controller::onPbFilePressed(string file)
{

}

void Controller::updateUi()
{
    // TODO: Mostrar los paneles en el menú, y al seleccionar un panel mostrar su información
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

    for(Panel panel : panelContents)
    {
        // std::cout << panel.toString() << std::endl; // DEBUG

        generateFiles(panel);

        cout << "Ended generating files for " + panel.getName() + "\n\n";
    }
}

Panel Controller::buildPanel(XMLElemento panel)
{
    // elementos obligatorios
    string type = panel.getAtributoValue("type");
    string name = panel.getAtributoValue("name");

    Panel panelObject = Panel(name);
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
                panelObject.setX(atoi(e.getSubelement("x").getContent().c_str()));
                panelObject.setY(atoi(e.getSubelement("y").getContent().c_str()));
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


void Controller::readUiXml(XMLFile ui)
{
    std::cerr << ui.toString();      // DEBUG

    XMLElemento root = ui.getRootElement();
    iterateXML(root);

    if (!currentPanel.getButtons().size()) {
        currentPanel.setType(PanelType::EXTERNAL_UI_READ);
    }
    else {
        currentPanel.setType(PanelType::EXTERNAL_UI_CONFIG);
    }

}

void Controller::iterateXML(XMLElemento e)
{
    vector<XMLElemento> subelementos = e.getElementos();
    for (XMLElemento i : subelementos)
    {
        if (i.getName().compare("class")) currentPanel.setName(i.getContent());
        string aux = i.getAtributoValue("class");
        if (!aux.compare("QPushButton"))
        {
            currentPanel.addButton(QPUSHBUTTON, i.getAtributoValue("name"));
            Controller::getInstance().printTrace(WARNING, "QPushButton: " + i.getAtributoValue("name"));
        }
        
        iterateXML(i);
        
    }
}
