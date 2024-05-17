#include "controller.h"
#include <iostream>
#include <string>

#include "model/generador.h"
#include <bits/getopt_core.h>


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
    int c;
    char* path;
    int nogui = 0;  // flag
    while ((c = getopt(_argc, _argv, "hn:")) != -1) {
    switch (c) 
        {
        case 'n':
            nogui=1;
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
    if (nogui)   // ejecución nogui
    {
        cout << "   - codeGenerator - no gui mode -\n\n";
        generateAllFiles(path);
        exit(EXIT_SUCCESS);
    }
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

GPanel* Controller::getCurrentPanel() const
{
    return currentPanel;
}

vector<string> Controller::getPanelNames() {
    return panelCol.getNames();
}

//----------------------------- HMI ---------------------------------
//-------------------------------------------------------------------

/**
 * Función llamada desde la vista, lee el archivo XML de entrada
 * y después genera los ficheros correspondientes.
*/
void Controller::onPbGeneratePressed()
{
    generateAllFiles("input.xml");
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

/**
 * Funcion llamada desde la vista, crea un nuevo panel y lo selecciona
 * como currentPanel para poder modificarlo desde el HMI. Si ya existe,
 * devuelve un valor false.
*/
bool Controller::onPbWithoutUIPressed(std::string name)
{
    if (panelCol.containsPanel(name))
    {
        return false;
    }
    panelCol.addPanel(name);
    currentPanel = panelCol.getPanelByName(name);
    return true;
}

/**
 * Funcion llamada desde la vista, añade a los botones la accion
 * seleccionada en el hmi
*/
bool Controller::onPbAssociatePressed(int button, int action)
{
    if (currentPanel == nullptr)
        return false;
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
bool Controller::onPbDeassociatePressed(int button)
{
    if (currentPanel == nullptr)
        return false;
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
void Controller::onPbSaveXmlPressed()
{
    XMLFile inputXml = XMLFile();
    inputXml.setXmlPath("input.xml");
    inputXml.writeXMLFile(panelCol);
}

/**
 * Función llamada desde la vista, lee un fichero XML con la configuración
 * del generador y devuelve el numero de paneles añadidos.
*/
int Controller::onPbLoadXmlPressed(string xmlPath)
{
    readInputXml(xmlPath);
    int addedPanels = panelCol.getPanelCollectionSize();
    currentPanel = panelCol.getPanelByIndex(0); // selecciona el primer panel
    return panelCol.getPanelCollectionSize();
}

/**
 * Funcion que añade un botón al currentPanel con la información recibida
 * como parametros desde la vista.
*/
void Controller::onPbAddButtonPressed(std::string name, std::string type, std::string action)
{
    if (currentPanel == nullptr)
        return;
    for (Button b : currentPanel->getButtons())
    {
        if (!b.getName().compare(name))
        {
            printTrace(INFO, "Button " + name + " alredy exists.");
            return;
        }
    }
    currentPanel->addButton(name, type, action);
}

/**
 * Borra el panel en la posición pasada como parámetro. Devuelve el número
 * de paneles restantes. Setea el currentPanel al ultimo panel de la
 * coleccion.
*/
int Controller::onPbDeletePanelPressed(std::string panel)
{
    panelCol.delPanel(panel);
    int newSize = panelCol.getLength();
    currentPanel = panelCol.getPanelByIndex(newSize - 1);
    return newSize;
}

/**
 * Función que elimina un botón del current panel.
*/
void Controller::onPbDelButtonPressed(int button)
{
    if (currentPanel == nullptr)
        return;
    currentPanel->deleteButton(button);
}

void Controller::changeCurrentPanel(int index)
{
    currentPanel = panelCol.getPanelByIndex(index);
}

/**
 * Función que trata de cambiar el layout del currentPanel. Devuelve
 * true en caso de cambiarlo y false en otro caso.
*/
bool Controller::onComboPanelsChanged(int index) 
{
    if (currentPanel != nullptr)
    {
        if(currentPanel->getLayout()!=EXTERNAL_UI) // si el ui ya viene dado, no cambiar nada
        {
            if (index==EXTERNAL_UI) // no se debe poder asignar este layout
            {
                printTrace(CRITICAL, "Controller::onComboPanelsChanged> cannot set EXTERNAL_UI layout");
            }
            else 
            {
                currentPanel->setLayout(static_cast<LayoutType>(index));
                return true;
            }
        }
    }
    return false;
}

/**
 * Función que trata de cambiar el tamaño del currentPanel. Devuelbe
 * true en caso de cambiarlo y false en otro caso.
*/
bool Controller::changeCurrentPanelSize(int h, int w)
{
    if (currentPanel != nullptr)
    {
        if(currentPanel->getLayout()!=EXTERNAL_UI) // si el ui ya viene dado, no cambiar nada
        {
            currentPanel->setHeight(h);
            currentPanel->setWidth(w);
            return true;
        }
    }
    return false;
}

string Controller::panelInfo()
{
    // string str = "";
    // for (GPanel p : panelCol.getVector())
    // {
    //     str += p.toString();
    //     str += "                    ____________________________________\n";
    // }
    // return str;
    return currentPanel->toString();
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
                if (se.numSubelements()==1) // si solo tiene el nombre, no la accion
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
        // elemento <layout>
        else if (!name.compare("layout"))
        {
            panelObject.setLayout(e.getContent());
        }
    }

    return panelObject;
}

/**
 * Dado el nombre de un archivo de entrada que es un XML de entrada
 * del generador, lee el documento XML y por cada elemento panel va
 * generando un elemento y añadiendolo a la colección de paneles.
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
    for(XMLElemento panel : doc.getRootElement().getElements()) {
        panelCol.addPanel(buildPanel(panel));
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
    XMLFile doc;

    try
    {
        doc = XMLFile(inputFile.data());
    }
    catch(const XMLFileException& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Error loading path '" << inputFile << "'\n";
        exit(EXIT_FAILURE);
    }
    cerr << doc.toString();
    for(XMLElemento panel : doc.getRootElement().getElements()) {
        panelCol.addPanelToGenerate(buildPanel(panel));
    }
    for (GPanel panel : panelCol.getVectorToGenerate())
    {
        generatePanelFiles(panel);
        printTrace(INFO, "Ended generating files for " + panel.getName() + "\n");
    }
}