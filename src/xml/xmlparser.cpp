#include "xmlparser.h"
#include <string>

#include "../controller.h"


// ----------------------------------------------------------------------
//  XMLAtributo
// ----------------------------------------------------------------------

XMLAtributo::XMLAtributo(string name, string valor) : name(name), valor(valor) {}

std::string XMLAtributo::getName() const {
    return name;
}

std::string XMLAtributo::getValor() const {
    return valor;
}

string XMLAtributo::toString() const
{
    return string("XMLAributo: [" + name + "] -> " + valor + "\n");
}

// ----------------------------------------------------------------------
//  XMLElemento
// ----------------------------------------------------------------------


XMLElemento::XMLElemento(string _name, string _content)
{
    name = _name;
    content = _content;
}

XMLElemento::XMLElemento(std::string name, std::string content, std::vector<XMLAtributo> atributos, std::vector<XMLElemento> elements) : 
    name(name), content(content), attributes(atributos), elements(elements) {}

std::string XMLElemento::getName() const {
    return name;
}

std::string XMLElemento::getContent() const {
    return content;
}

std::vector<XMLAtributo> XMLElemento::getAttributes() {
    return attributes;
}

std::vector<XMLElemento> XMLElemento::getElements() {
    return elements;
}

/**
 * Función que devuelve el valor de un atributo, o cadena vacía si no existe.
 * 
 * @param name Cadena con el nombre del atributo
 * @return Cadena con el valor del atributo, o cadena vacía en caso de fallo.
*/
std::string XMLElemento::getAtributoValue(std::string name)
{
    for (XMLAtributo atributo : attributes)
    {
        if (!atributo.getName().compare(name))
            return atributo.getValor();
    }
    Controller::getInstance().printTrace(DEBUG, "Attribute '" + name + "' does not exist.");
    return "";
}

/**
 * Función que busca entre los subelementos de un objeto XMLElemento, y 
 * devuelve el primero que encuentre con el nombre deseado.
 * 
 * @param name Cadena con el nombre del subelemento
 * @return Elemento con el nombre buscado.
 * @throws XMLElementNotFoundException en caso de que no exista un subelemento
 * con ese nombre.
*/
XMLElemento XMLElemento::getSubelement(string name)
{
    for (XMLElemento e : elements)
    {
        if (!e.getName().compare(name))
            return e;
    }
    string what = "No existe el elemento " + name;
    throw XMLElementNotFoundException(what.c_str());
}

void XMLElemento::addSubelement(XMLElemento e) 
{
    elements.push_back(e);
}

void XMLElemento::addAttribute(XMLAtributo a)
{
    attributes.push_back(a);
}

void XMLElemento::addAttribute(string name, string data)
{
    XMLAtributo a = XMLAtributo(name, data);
    attributes.push_back(a);
}

int XMLElemento::numSubelements() const
{
    return elements.size();
}

string XMLElemento::toString(int depth) const
{   
    string str, space = "";

    for (int i=0;i<depth;i++)
    {
        space += "| ";
    }
    depth++;
    str += "XMLElemento: [" + name + "]";
    if (!content.empty())
    {
        str += " -> " + content;
    }
    str += "\n";
    for (XMLAtributo a : attributes)
    {
        str += space + a.toString();
    }
    for (XMLElemento e : elements)
    {
        str += space + e.toString(depth);
    }
    
    return str;
}

// ----------------------------------------------------------------------
//  XMLFile
// ----------------------------------------------------------------------

/**
 * Desde el constructor se carga el documento XML con la librería externa
 * y se parsea como un elemento XMLFile con sus respectivos subelementos.
*/
XMLFile::XMLFile(char* _xmlPath) {
    xmlPath = _xmlPath;
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(xmlPath) != tinyxml2::XML_SUCCESS) {
        throw XMLBaseException("Error loading XML file");
    }

    const tinyxml2::XMLElement* root = doc.FirstChildElement();
    rootElement = parseElement(root);
}

char * XMLFile::getXmlPath() const {
    return xmlPath;
}

char * XMLFile::getDtdPath() const {
    return dtdPath;
}

void XMLFile::setXmlPath(char *path)
{
    xmlPath = path;
}

void XMLFile::setRoot(XMLElemento root)
{
    rootElement = root;
}

XMLElemento XMLFile::getRootElement() const {
    return rootElement;
}

/**
 * Escribe con formato XML los paneles existentes en panels en el
 * fichero input.xml, implementa funcionalidad de la libreria externa.
*/
void XMLFile::writeXMLFile(PanelCollection panels)
{
    tinyxml2::XMLDocument doc;
    
    tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
    doc.InsertFirstChild(decl);
    
    // root element <panels>
    tinyxml2::XMLElement* root = doc.NewElement("panels");
    doc.InsertEndChild(root);

    // insertar cada panel
    for (GPanel p : panels.getVector())
    {
        tinyxml2::XMLElement* panel = doc.NewElement("panel");
        
        panel->SetAttribute("name",p.getName().data());
        panel->SetAttribute("type",PanelTypeToString[p.getType()].data());
        root->InsertEndChild(panel);

        // añadir su layout si no es el default
        if (p.getLayout()!=DEFAULT_LAYOUT)
        {
            tinyxml2::XMLElement* layout = doc.NewElement("layout");
            layout->SetText(LayoutTypeToString[p.getLayout()].data());
            panel->InsertEndChild(layout);
        }
        
        // añadir el tamaño si no es el default
        if (p.getHeight()!=DEFAULT_H || p.getWidth()!=DEFAULT_W)
        {
            tinyxml2::XMLElement* geometry = doc.NewElement("geometry");
            tinyxml2::XMLElement* height = doc.NewElement("h");
            tinyxml2::XMLElement* width = doc.NewElement("w");
            height->SetText(p.getHeight());
            width->SetText(p.getWidth());
            geometry->InsertEndChild(height);
            geometry->InsertEndChild(width);
            panel->InsertEndChild(geometry);
        }

        PanelType tipo = p.getType();
        // si es de tipo ui externo, añadir el path del ui
        if (tipo == EXTERNAL_UI_CONFIG || tipo == EXTERNAL_UI_READ)
        {
            tinyxml2::XMLElement* uipath = doc.NewElement("uipath");
            uipath->SetText(p.getUiPath().data());
            panel->InsertEndChild(uipath);
        }
        // si es de tipo config, añadir los botones
        if (tipo == EXTERNAL_UI_CONFIG || tipo == CONFIG)
        {
            tinyxml2::XMLElement* buttonsElement = doc.NewElement("buttons");
            panel->InsertEndChild(buttonsElement);
            for (Button b : p.getButtons())
            {
                tinyxml2::XMLElement* button = doc.NewElement("button");
                button->SetAttribute("type",ButtonTypeToString[b.getType()].data());
                buttonsElement->InsertEndChild(button);
                
                tinyxml2::XMLElement* name = doc.NewElement("name");
                name->SetText(b.getName().data());
                button->InsertEndChild(name);
                if (b.getAction() != NULLBUTTONACTION)
                {
                    tinyxml2::XMLElement* action = doc.NewElement("action");
                    action->SetText(ButtonActionToString[b.getAction()].data());
                    button->InsertEndChild(action);
                }
            }
        }
        // TODO: continuar con condiciones, si no tiene ui, más elementos, etc.
    }
    
    // guardar el documento
    if (doc.SaveFile(xmlPath) == tinyxml2::XML_SUCCESS) {
        Controller::getInstance().printTrace(INFO, "XMLFile succesfully saved in " + std::string(xmlPath));
    } else {
        Controller::getInstance().printTrace(ERROR, "Error saving file:" + std::string(xmlPath));        
    }
}

string XMLFile::toString() const
{
    int depth = 1;
    std::string str;
    str = "Class=XMLFile\n";
    str += "{\n";
    str += "xmlPath=[" + string(xmlPath) + "]\n";
    str += "dtdPath=[" + string(dtdPath) + "]\nElements:\n";
    str += rootElement.toString(depth) + "}\n";

    return str;
}

/**
 * Implementa la funcionalidad de la librería externa. Rellena el objeto XMLFile
 * con los elementos y atributos correspondientes que va creando a medida que
 * tinyxml2 va parseando el documento.
*/
XMLElemento XMLFile::parseElement(const tinyxml2::XMLElement* e) {
    // elementos directamente obtenibles
    string name = e->Name();
    string content;
    if (e->GetText()) {
        content = e->GetText();
    }
    // si hubiese atributos también son directamente obtenibles
    vector<XMLAtributo> atributos;
    for (const tinyxml2::XMLAttribute* attr = e->FirstAttribute(); attr; attr = attr->Next()) {
        atributos.push_back(XMLAtributo(attr->Name(), attr->Value()));
    }

    // de forma recursiva va parseando elementos y subelementos
    vector<XMLElemento> subelementos;
    for (const tinyxml2::XMLElement* subelement = e->FirstChildElement(); subelement; subelement = subelement->NextSiblingElement()) {
        subelementos.push_back(parseElement(subelement));
    }

    // cuando tiene todo parseado devuelve el elemento a la función anterior
    
    return XMLElemento(name, content, atributos, subelementos);

    
}
