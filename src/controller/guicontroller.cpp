#include "guicontroller.h"


GuiController::GuiController() {}

GuiController::~GuiController() {}

//----------------------------- HMI ---------------------------------
//-------------------------------------------------------------------

/**
 * Función llamada desde la vista, lee el archivo XML de entrada
 * y después genera los ficheros correspondientes.
*/
void GuiController::onPbGeneratePressed(string outDirectory)
{
    generateAllFiles(outDirectory);
}

/**
 * Funcion llamada desde la vista, maneja la lectura del archivo
 * .ui y la formación del panel correspondiente. Si el panel ya
 * existe, devuelve un valor booleano de false a la interfaz para
 * que avise por pantalla.
*/
bool GuiController::onPbWithUIPressed(string uiPath)
{        
    XMLFile uiXml(uiPath.data());
    try
    {
        uiXml.read(); // lee el archivo .ui
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
bool GuiController::onPbWithoutUIPressed(std::string name)
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
bool GuiController::onPbAssociatePressed(int button, int action)
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
bool GuiController::onPbDeassociatePressed(int button)
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
void GuiController::onPbSaveXmlPressed(std::string xmlPath)
{
    XMLParser parser;
    parser.writeXMLFile(panelCol, xmlPath);
}

/**
 * Función llamada desde la vista, lee un fichero XML con la configuración
 * del generador y devuelve el numero de paneles añadidos.
*/
int GuiController::onPbLoadXmlPressed(string xmlPath)
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
void GuiController::onPbAddButtonPressed(std::string name, std::string type, std::string action)
{
    if (currentPanel == nullptr)
        return;
    for (Button b : currentPanel->getButtons())
    {
        if (b.getName() == name)
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
int GuiController::onPbDeletePanelPressed(std::string panel)
{
    panelCol.delPanel(panel);
    int newSize = panelCol.getLength();
    currentPanel = panelCol.getPanelByIndex(newSize - 1);
    return newSize;
}

/**
 * Función que elimina un botón del current panel.
*/
void GuiController::onPbDelButtonPressed(int button)
{
    if (currentPanel == nullptr)
        return;
    currentPanel->deleteButton(button);
}

void GuiController::changeCurrentPanel(int index)
{
    currentPanel = panelCol.getPanelByIndex(index);
}

/**
 * Función que trata de cambiar el layout del currentPanel. Devuelve
 * true en caso de cambiarlo y false en otro caso.
*/
bool GuiController::onComboPanelsChanged(int index) 
{
    if (currentPanel != nullptr)
    {
        if(currentPanel->getLayout()!=EXTERNAL_UI) // si el ui ya viene dado, no cambiar nada
        {
            if (index==EXTERNAL_UI) // no se debe poder asignar este layout
            {
                printTrace(CRITICAL, "GuiController::onComboPanelsChanged> cannot set EXTERNAL_UI layout");
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

void GuiController::onHeaderSavePressed(SaesHeader* header)
{
    if (currentPanel != nullptr)
    {
        for(int i = 0; i < HeaderElement::NOELEMENTS; i++)
        {   
            HeaderElement elem = static_cast<HeaderElement>(i);
            currentPanel->setHeaderElement(elem, header->getHeaderElement(elem));
        }
    }
}

/**
 * Función que trata de cambiar el tamaño del currentPanel. Devuelve
 * true en caso de cambiarlo y false en otro caso.
*/
bool GuiController::changeCurrentPanelSize(int h, int w)
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

/**
 * Función que devuelve un string con la información del panel actual.
*/
string GuiController::panelInfo()
{
    return currentPanel->toString();
}