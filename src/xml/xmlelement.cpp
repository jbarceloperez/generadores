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

XMLElement::XMLElement(std::string name, std::string content, std::vector<XMLAttribute> atributos, std::vector<XMLElement> elements) : 
    name(name), content(content), attributes(atributos), elements(elements) {}

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
        if (!atributo.getName().compare(name))
            return atributo.getValor();
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
        if (!e.getName().compare(name))
            return e;
    }
    string what = "No existe el elemento " + name;
    throw XMLElementNotFoundException(what.c_str());
}

void XMLElement::addSubelement(XMLElement e) 
{
    elements.push_back(e);
}

void XMLElement::addAttribute(XMLAttribute a)
{
    attributes.push_back(a);
}

void XMLElement::addAttribute(string name, string data)
{
    XMLAttribute a = XMLAttribute(name, data);
    attributes.push_back(a);
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

/**
 * Dado un elemento panel obtenido del XML de entrada, recorre sus propiedades
 * y crea un objeto panel acorde a estas propiedades.
*/
GPanel XMLElement::buildPanel()
{
    if (name.compare("panel"))
        return GPanel("");
    // elementos obligatorios
    string type = getAttributeValue("type");
    string name = getAttributeValue("name");

    GPanel panelObject = GPanel(name);
    panelObject.setType(type);

    // otros elementos
    for (XMLElement e : elements) {
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
            for (XMLElement se : e.getElements())
            {
                if (se.numSubelements()==1) // si solo tiene el nombre, no la accion
                    panelObject.addButton(se.getSubelement("name").getContent(), se.getAttributeValue("type"), "null");
                else
                    panelObject.addButton(se.getSubelement("name").getContent(), se.getAttributeValue("type"), se.getSubelement("action").getContent());
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