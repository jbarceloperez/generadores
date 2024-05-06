#include "controller.h"
#include <iostream>
#include <string>

#include "model/generador.h"


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
    dbg::log::initialize("/home/javi/Documentos/Generadores/src/traces.cfg");
    appLogLevel = TRACE;
    currentPanel = nullptr;

}

// todo: fix logger
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

GPanel Controller::getCurrentPanel() const
{
    return *currentPanel;
}

//----------------------------- HMI ---------------------------------
//-------------------------------------------------------------------

/**
 * Función llamada desde la vista, lee el archivo XML de entrada
 * y después genera los ficheros correspondientes.
*/
void Controller::onPbGeneratePressed()
{
    readInputXml("input.xml");
    generateAllFiles();
}

/**
 * Funcion llamada desde la vista, maneja la lectura del archivo
 * .ui y la formación del panel correspondiente. Si el panel ya
 * existe, devuelve un valor booleano de false a la interfaz para
 * que avise por pantalla.
*/
bool Controller::onPbWithUIPressed(string uiPath)
{        
    XMLFile uiXml;
    try
    {
        uiXml = XMLFile(uiPath.data()); // lee el archivo .ui
    }   
    catch(const XMLFileException& e)
    {   // TODO: Manejar el error en vez de excepción
        printTrace(CRITICAL, e.what());
        printTrace(CRITICAL, "Error loading path '" + uiPath + "'\n");
    }
    if (readUiXml(uiXml))   // si el panel ya existe devuelve falso
        return true;
    return false;    
}

void Controller::onPbWithoutUIPressed()
{
    // TODO: funcionalidad panel vacío
}

/**
 * Funcion llamada desde la vista, añade a los botones la accion
 * seleccionada en el hmi
*/
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

/**
 * Funcion llamada desde la vista, borra la acción de un botón concreto
*/
bool Controller::onPbDeassociatePressed(int button, int action)
{
    if (currentPanel->getButtons()[button].getAction() != NULLBUTTONACTION)
    {   
        currentPanel->deleteActionToButton(button);
        return true;
    }
    return false;
}

/**
 * Función llamada desde la vista, escribe el objeto XMLFile en
 * un fichero.
*/
void Controller::onPbXmlPressed()
{
    XMLFile inputXml = XMLFile();
    inputXml.setXmlPath("input.xml");
    inputXml.writeXMLFile(panelCol);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------

/**
 * Lee el archivo XML con la ui del panel a crear, y crea y añade a la
 * colección dicho panel con las propiedades detectadas en el .ui
*/
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

/**
 * Hace un recorrido primero en profundidad el XML, buscando elementos
 * botón y añadiéndolos al objeto panel.
*/
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

/**
 * Dado un elemento panel obtenido del XML de entrada, recorre sus propiedades
 * y crea un objeto panel acorde a estas propiedades.
*/
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

/**
 * Dado el nombre de un archivo de entrada que es un XML de entrada
 * del generador, lee el documento XML y por cada elemento panel va
 * generando un elemento 
*/
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
}

/**
 * Para cada panel en la colección, llama a la lógica del generador para
 * generar su estructura de clases.
*/
void Controller::generateAllFiles()
{
    for (GPanel panel : panelCol.getVector())
    {
        generatePanelFiles(panel);
        cout << "Ended generating files for " + panel.getName() + "\n\n";
    }
}