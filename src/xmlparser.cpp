#include "xmlparser.h"
#include <string>
#include <iostream>

using namespace tinyxml2;

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
    // TODO
    return string();
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
 * Función que devuelve el valor de un atributo.
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
    throw XMLElementNotFoundException("No existe el elemento " + name);
}

void XMLElemento::addSubelemento(XMLElemento e) {
    elements.push_back(e);
}

int XMLElemento::numSubelements() const{
    return elements.size();
}

string XMLElemento::toString() const
{   
    // TODO
    return string();
}

//
//  XMLData
//



//
//  XMLDoc
//

XMLDoc::XMLDoc(char* _xmlPath) {
    xmlPath = _xmlPath;
    XMLDocument doc;
    if (doc.LoadFile(xmlPath) != XML_SUCCESS) {
        throw XMLException("Error loading XML file");
    }

    const XMLElement* root = doc.FirstChildElement("panels");
    if (!root) {
        throw XMLParseException("Error finding root element 'panels'");
    }
    
    rootElement = parseElement(root);
}

XMLDoc::XMLDoc() {}

XMLDoc::~XMLDoc() {}

char * XMLDoc::getXmlPath() const {
    return xmlPath;
}

char * XMLDoc::getDtdPath() const {
    return dtdPath;
}

XMLElemento XMLDoc::getRootElement() const {
    return rootElement;
}

string XMLDoc::toString() const
{
    std::string str;
    str = "Class=XMLDoc\n";
    str += "{\n";
    str += "\txmlPath=[" + string(xmlPath) + "]\n";
    str += "\tdtdPath=[" + string(dtdPath) + "]\n\tElements:\n{";
    str += rootElement.toString() + "}\n";
    str += "}\n";

    return str;
}

/**
 * Implementa la funcionalidad de la librería externa. Rellena el objeto XMLDoc
 * con los elementos y atributos correspondientes que va creando a medida que
 * tinyxml2 va parseando el documento.
*/
XMLElemento XMLDoc::parseElement(const XMLElement* e) {
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
