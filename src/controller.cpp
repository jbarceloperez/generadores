#include "controller.h"
#include <iostream>
#include <string>

#include "model/generador.h"

std::string NULL_STRING = "";

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
    dbg::log::initialize("/home/javi/Documentos/Generadores/src/traces.cfg");
    appLogLevel = TRACE;
    currentPanel = nullptr;

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
    readInputXml("input.xml");
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

bool Controller::onPbAssociatePressed(int button, int action)
{
    ButtonAction a = static_cast<ButtonAction>(action);
    if (currentPanel->getButtons()[button].getAction() != a)
    {
        currentPanel->addActionToButton(button, a);
        return true;
    }
    return false;
}

void Controller::onPbDeassociatePressed()
{

}

void Controller::onPbXmlPressed()
{
    XMLFile inputXml = XMLFile();
    inputXml.setXmlPath("input.xml");
    inputXml.writeXMLFile(panelCol);
}

GPanel Controller::getCurrentPanel() const
{
    return *currentPanel;
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
    XMLFile doc;

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

    for(XMLElemento panel : doc.getRootElement().getElements()) {
        panelCol.addPanel(buildPanel(panel));
    }


    // a este punto ya debería tener los paneles claros, ahora toca
    // decidir cómo los va a generar cada uno, en su subcarpeta y con
    // sus características

    for(GPanel panel : panelCol.getVector())
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
    for (XMLElemento e : panel.getElements()) {
        string name = e.getName();
        // elemento <geometry>
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
        // elemento <buttons>
        else if (!name.compare("buttons"))
        {
            for (XMLElemento se : e.getElements())
            {
                if (se.numSubelements()==1)
                    panelObject.addButton(se.getSubelement("name").getContent(), se.getAtributoValue("type"), "null");
                else
                    panelObject.addButton(se.getSubelement("name").getContent(), se.getAtributoValue("type"), se.getSubelement("action").getContent());
            }
        }
        // elmento <uipath>
        else if (!name.compare("uipath"))
        {
            panelObject.setUiPath(e.getContent());
        }
    }

    return panelObject;
}

void Controller::readInputXml(string inputFileName)
{
    XMLFile doc;

    try
    {
        doc = XMLFile(inputFileName.data());
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

    for(XMLElemento panel : doc.getRootElement().getElements()) {
        panelCol.addPanel(buildPanel(panel));
    }

    for(GPanel panel : panelCol.getVector())
    {
        generateFiles(panel);
        cout << "Ended generating files for " + panel.getName() + "\n\n";
    }
}

bool Controller::readUiXml(XMLFile ui)
{
    XMLElemento root = ui.getRootElement();
    // get the name
    std::string name = root.getSubelement("class").getContent();
    if (panelCol.containsPanel(name))
    {
        printTrace(INFO, "Same panel '" + name + "' alredy loaded. Ignoring.");
        return false;
    }
    // nuevo panel
    panelCol.addPanel(name);
    currentPanel = panelCol.getPanelFromPanelCol(name);
    
    printTrace(TRACE, "Loaded panel '" + name + "'");
    currentPanel->setUiPath(ui.getXmlPath());
    iterateXML(root);
    if (!currentPanel->getButtons().size()) {
        currentPanel->setType(PanelType::EXTERNAL_UI_READ);
    }
    else {
        currentPanel->setType(PanelType::EXTERNAL_UI_CONFIG);
    }
    return true;
}

void Controller::iterateXML(XMLElemento e)
{
    vector<XMLElemento> subelementos = e.getElements();
    for (XMLElemento i : subelementos)
    {
        string aux = i.getAtributoValue("class");
        if (!aux.compare("QPushButton"))
        {
            currentPanel->addButton(QPUSHBUTTON, i.getAtributoValue("name"));
            Controller::getInstance().printTrace(WARNING, "QPushButton: " + i.getAtributoValue("name"));
        }
        iterateXML(i);
    }
}
