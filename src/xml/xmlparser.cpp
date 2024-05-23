#include "xmlparser.h"
#include <string>
#include <iostream>

#include "../controller.h"


// ----------------------------------------------------------------------
//  XMLAttribute
// ----------------------------------------------------------------------

XMLAttribute::XMLAttribute(string name, string valor) : name(name), valor(valor) {}

std::string XMLAttribute::getName() const {
    return name;
}

std::string XMLAttribute::getValor() const {
    return valor;
}

string XMLAttribute::toString() const
{
    return string("XMLAributo: [" + name + "] -> " + valor + "\n");
}

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

// ----------------------------------------------------------------------
//  XMLFile
// ----------------------------------------------------------------------

/**
 * Desde el constructor se carga el documento XML con la librería externa
 * y se parsea como un elemento XMLFile con sus respectivos subelementos.
*/
XMLFile::XMLFile(char* _xmlPath) {
    xmlPath = _xmlPath;
    read();
}

void XMLFile::read()
{
    QFile file(xmlPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw XMLFileException("Error al abrir el archivo XML.");
    }

    QXmlStreamReader xmlReader(&file);
    xmlReader.readNextStartElement();
    rootElement = parseElement(xmlReader);
    std::cerr << toString();    // DEBUG
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

void XMLFile::setRoot(XMLElement root)
{
    rootElement = root;
}

XMLElement XMLFile::getRootElement() const {
    return rootElement;
}

/**
 * Escribe con formato XML los paneles existentes en panels en el
 * fichero input.xml, implementa funcionalidad de la libreria externa.
*/
void XMLFile::writeXMLFile(PanelCollection panels)
{
    // tinyxml2::XMLDocument doc;
    
    // tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
    // doc.InsertFirstChild(decl);
    
    // // root element <panels>
    // tinyxml2::XMLElement* root = doc.NewElement("panels");
    // doc.InsertEndChild(root);

    // // insertar cada panel
    // for (GPanel p : panels.getVector())
    // {
    //     tinyxml2::XMLElement* panel = doc.NewElement("panel");
        
    //     panel->SetAttribute("name",p.getName().data());
    //     panel->SetAttribute("type",PanelTypeToString[p.getType()].data());
    //     root->InsertEndChild(panel);

    //     // añadir su layout si no es el default
    //     if (p.getLayout()!=DEFAULT_LAYOUT)
    //     {
    //         tinyxml2::XMLElement* layout = doc.NewElement("layout");
    //         layout->SetText(LayoutTypeToString[p.getLayout()].data());
    //         panel->InsertEndChild(layout);
    //     }
        
    //     // añadir el tamaño si no es el default
    //     if (p.getHeight()!=DEFAULT_H || p.getWidth()!=DEFAULT_W)
    //     {
    //         tinyxml2::XMLElement* geometry = doc.NewElement("geometry");
    //         tinyxml2::XMLElement* height = doc.NewElement("h");
    //         tinyxml2::XMLElement* width = doc.NewElement("w");
    //         height->SetText(p.getHeight());
    //         width->SetText(p.getWidth());
    //         geometry->InsertEndChild(height);
    //         geometry->InsertEndChild(width);
    //         panel->InsertEndChild(geometry);
    //     }

    //     PanelType tipo = p.getType();
    //     // si es de tipo ui externo, añadir el path del ui
    //     if (tipo == EXTERNAL_UI_CONFIG || tipo == EXTERNAL_UI_READ)
    //     {
    //         tinyxml2::XMLElement* uipath = doc.NewElement("uipath");
    //         uipath->SetText(p.getUiPath().data());
    //         panel->InsertEndChild(uipath);
    //     }
    //     // si es de tipo config, añadir los botones
    //     if (tipo == EXTERNAL_UI_CONFIG || tipo == CONFIG)
    //     {
    //         tinyxml2::XMLElement* buttonsElement = doc.NewElement("buttons");
    //         panel->InsertEndChild(buttonsElement);
    //         for (Button b : p.getButtons())
    //         {
    //             tinyxml2::XMLElement* button = doc.NewElement("button");
    //             button->SetAttribute("type",ButtonTypeToString[b.getType()].data());
    //             buttonsElement->InsertEndChild(button);
                
    //             tinyxml2::XMLElement* name = doc.NewElement("name");
    //             name->SetText(b.getName().data());
    //             button->InsertEndChild(name);
    //             if (b.getAction() != NULLBUTTONACTION)
    //             {
    //                 tinyxml2::XMLElement* action = doc.NewElement("action");
    //                 action->SetText(ButtonActionToString[b.getAction()].data());
    //                 button->InsertEndChild(action);
    //             }
    //         }
    //     }
    //     // TODO: continuar con condiciones, si no tiene ui, más elementos, etc.
    // }
    
    // // guardar el documento
    // if (doc.SaveFile(xmlPath) == tinyxml2::XML_SUCCESS) {
    //     Controller::getInstance().printTrace(INFO, "XMLFile succesfully saved in " + std::string(xmlPath));
    // } else {
    //     Controller::getInstance().printTrace(ERROR, "Error saving file:" + std::string(xmlPath));        
    // }
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
 * el QXmlStreamReader de Qt va parseando el documento.
*/
XMLElement XMLFile::parseElement(QXmlStreamReader& xmlReader) {

    // nombre y atributos del elemento
    QString name = xmlReader.name().toString();
    
    // procesa los atributos
    vector<XMLAttribute> atributos;
    const QXmlStreamAttributes xmlAttributes = xmlReader.attributes();
    for (const QXmlStreamAttribute& attr : xmlAttributes)   // lista de atributos
    {
        atributos.push_back(XMLAttribute(attr.name().toString().toStdString(), attr.value().toString().toStdString()));
    }

    // añade el texto del elemento
    QString content("");
    // xmlReader.readNext();
    // if (xmlReader.tokenType() == QXmlStreamReader::Characters && !xmlReader.isWhitespace())
    // {
    //     if (!xmlReader.readElementText().isEmpty()) 
    //     {
    //         content = xmlReader.readElementText();
    //     }
    // }

    // de forma recursiva va parseando elementos y subelementos
    vector<XMLElement> subelementos;
    // while (xmlReader.readNextStartElement())
    // {
    //     subelementos.push_back(parseElement(xmlReader));
    // }
    while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == name)) {
        xmlReader.readNext();
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) 
        {
            subelementos.push_back(parseElement(xmlReader));
        } 
        else if (xmlReader.tokenType() == QXmlStreamReader::Characters && !xmlReader.isWhitespace()) 
        {
            content = xmlReader.text().toString();
        }
    }

    // cuando tiene todo parseado devuelve el elemento a la función anterior
    
    return XMLElement(name.toStdString(), content.toStdString(), atributos, subelementos);
}
