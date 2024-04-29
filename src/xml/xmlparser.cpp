#include "xmlparser.h"
#include <string>

#include "../controller.h"


//
//  XMLAtributo
//

XMLAtributo::XMLAtributo() {}

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

//
//  XMLElemento
//

XMLElemento::XMLElemento() { }

XMLElemento::XMLElemento(std::string name, std::string content, std::vector<XMLAtributo> atributos, std::vector<XMLElemento> elements) : 
    name(name), content(content), attributes(atributos), elements(elements) {}

std::string XMLElemento::getName() const {
    return name;
}

std::string XMLElemento::getContent() const {
    return content;
}


std::vector<XMLAtributo> XMLElemento::getAtributos() {
    return attributes;
}

std::vector<XMLElemento> XMLElemento::getElementos() {
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

void XMLElemento::addSubelemento(XMLElemento e) {
    elements.push_back(e);
}

int XMLElemento::numSubelements() const{
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

//
//  XMLData
//



//
//  XMLFile
//

XMLFile::XMLFile(char* _xmlPath) {
    xmlPath = _xmlPath;
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(xmlPath) != tinyxml2::XML_SUCCESS) {
        throw XMLBaseException("Error loading XML file");
    }

    const tinyxml2::XMLElement* root = doc.FirstChildElement();
    // const XMLElement* root = doc.FirstChildElement("panels");
    // if (!root) {
    //     // throw XMLParseException("Error finding root element: no <panels> element.");
    //     std::cerr << "No <panels> element \n";
    //     root = doc.FirstChildElement();
    // }
    
    rootElement = parseElement(root);
}

XMLFile:: XMLFile() {}

XMLFile::~XMLFile() {}

char * XMLFile::getXmlPath() const {
    return xmlPath;
}

char * XMLFile::getDtdPath() const {
    return dtdPath;
}

XMLElemento XMLFile::getRootElement() const {
    return rootElement;
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
