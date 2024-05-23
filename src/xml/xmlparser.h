#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <vector>
#include <exception>
#include "../model/panel.h"
#include "../model/panelcollection.h"

// Librería externa para wrappear las clases XML
#include <QXmlStreamReader>
#include <QFile>
#include <QString>

using namespace std;

/**
 * Tipo de excepción genérico para el código del wrapper.
*/
class XMLBaseException : public exception {
private:
    const char* m_message;
public:
    XMLBaseException(const char* message) : m_message(message) {}

    const char* what() const noexcept override {
        return m_message;
    }
};

/**
 * Excepción que hereda de XMLBaseException, lanzada al haber un fallo en la lectura del input
*/
class XMLFileException : public XMLBaseException {
public:
    using XMLBaseException::XMLBaseException;
};

/**
 * Excepción que hereda de XMLBaseException, para cunado haya un fallo al parsear el archivo
*/
class XMLParseException : public XMLBaseException {
public:
    using XMLBaseException::XMLBaseException;
};

/**
 * Excepción que hereda de XMLBaseException, para cuando falle la búsqueda de un elemento concreto
*/
class XMLElementNotFoundException : public XMLBaseException {
public:
    using XMLBaseException::XMLBaseException;
};

/**
 * Excepción que hereda de XMLBaseException, para cuando falle la búsqueda de un atributo concreto
*/
class XMLAtributeNotFoundException : public XMLBaseException {
public:
    using XMLBaseException::XMLBaseException;
};

/**
 * Clase que representa un atributo de un elemento XML. Tiene dos string privados
 * que representan el nombre y el valor del atributo.
*/
class XMLAttribute {

private:
    // Nombre del atributo
    string name;
    // Cadena con el valor del atributo
    string valor;

public:
    XMLAttribute() {};
    // Constructor que inicializa los atributos
    XMLAttribute(string name, string valor);
    
    string getName() const;
    string getValor() const;

    string toString() const;
    
};

/**
 * Clase que representa un elemento del fichero XML. Tiene cadenas que 
 * representan el nombre y el valor del elemento, si lo tuviese. Además,
 * tiene dos colecciones, un es vector<XMLAttribute> que representa los
 * atributos del elemento, y otro vector<XMLElement> que representa los
 * hijos que pueda tener el elemento.
 * 
 * TODO: Implementar relaciones padre-hijo entre elementos de alguna manera
*/
class XMLElement {

private:
    vector<XMLAttribute> attributes;
    vector<XMLElement> elements;
    string name;
    string content;


public:
    XMLElement() {};
    XMLElement(string name, string content);
    XMLElement(string name, string content, vector<XMLAttribute> atributos, vector<XMLElement> elements);

    string getName() const;
    string getContent() const;
    vector<XMLAttribute> getAttributes();
    vector<XMLElement> getElements();

    string getAttributeValue(string name);
    XMLElement getSubelement(string name);
    void addSubelement(XMLElement e);   
    void addAttribute(XMLAttribute a); 
    void addAttribute(string name, string data);
    int numSubelements() const;
    string toString(int depth) const;
};

/**
 * Clase que representa el documento XML a leer. Tiene como atributos el
 * path al xml y al dtd. Tiene el elemento raíz como atributo privado, y es 
 * en esta clase donde se implementa la funcionalidad de la librería externa.
*/
class XMLFile {

private:
    char * xmlPath;
    char * dtdPath;
    XMLElement rootElement;

    XMLElement parseElement(QXmlStreamReader& xml);

public:
    XMLFile(char * xmlPath);
    XMLFile() {};

    ~XMLFile() {};

    void read();
    XMLElement getRootElement() const;
    char * getXmlPath() const;
    char * getDtdPath() const;
    void setXmlPath(char * path);
    void setRoot(XMLElement root);
    
    void writeXMLFile(PanelCollection panels);

    string toString() const;

};

#endif
