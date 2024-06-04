#include "xmlelement.h"
#include "../controller.h"


// ----------------------------------------------------------------------
//  XMLElemento
// ----------------------------------------------------------------------


XMLElement::XMLElement(string _name, string _content)
{
    name = _name;
    content = _content;
}

XMLElement::XMLElement(std::string name, std::string content, std::vector<XMLAttribute> attributes, std::vector<XMLElement> elements) : 
    name(name), content(content), attributes(attributes), elements(elements) {}

std::string XMLElement::getName() const {
    return name;
}

std::string XMLElement::getContent() const {
    return content;
}

std::vector<XMLAttribute> XMLElement::getAttributes() {
    return attributes;
}

std::vector<XMLElement> XMLElement::getElements() {
    return elements;
}

/**
 * Función que devuelve el valor de un atributo, o cadena vacía si no existe.
 * 
 * @param name Cadena con el nombre del atributo
 * @return Cadena con el valor del atributo, o cadena vacía en caso de fallo.
*/
std::string XMLElement::getAttributeValue(std::string name)
{
    for (XMLAttribute atributo : attributes)
    {
        if (atributo.getName() == name)
            return atributo.getValue();
    }
    Controller::getInstance().printTrace(DEBUG, "Attribute '" + name + "' does not exist.");
    return "";
}

/**
 * Función que busca entre los subelementos de un objeto XMLElement, y 
 * devuelve el primero que encuentre con el nombre deseado.
 * 
 * @param name Cadena con el nombre del subelemento
 * @return Elemento con el nombre buscado.
 * @throws XMLElementNotFoundException en caso de que no exista un subelemento
 * con ese nombre.
*/
XMLElement XMLElement::getSubelement(string name)
{
    for (XMLElement e : elements)
    {
        if (e.getName() == name)
            return e;
    }
    string what = "No existe el elemento " + name;
    throw XMLElementNotFoundException(what.c_str());
}

void XMLElement::addSubelement(XMLElement elem) 
{
    elements.push_back(elem);
}

void XMLElement::addAttribute(XMLAttribute attr)
{
    attributes.push_back(attr);
}

void XMLElement::addAttribute(string name, string data)
{
    XMLAttribute attr = XMLAttribute(name, data);
    attributes.push_back(attr);
}

int XMLElement::numSubelements() const
{
    return elements.size();
}

string XMLElement::toString(int depth) const
{   
    string str, space = "";

    for (int i=0;i<depth;i++)
    {
        space += "| ";
    }
    depth++;
    str += "XMLElement: [" + name + "]";
    if (!content.empty())
    {
        str += " -> " + content;
    }
    str += "\n";
    for (XMLAttribute a : attributes)
    {
        str += space + a.toString();
    }
    for (XMLElement e : elements)
    {
        str += space + e.toString(depth);
    }
    
    return str;
}