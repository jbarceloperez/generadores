#include <string>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include "tinyxml2.h"

#ifndef XMLPARSER_H
#define XMLPARSER_H

#define XMLNULL -1

using namespace std;

/**
 * Tipo de excepción genérico para el código del wrapper.
*/
class XMLException : public std::exception {
public:
    XMLException(const std::string& message) : m_message(message) {}

    const char* what() const noexcept override {
        return m_message.c_str();
    }

private:
    std::string m_message;
};

/**
 * Excepción que hereda de XMLException, lanzada al haber un fallo en la lectura del input
*/
class XMLFileException : public XMLException {
public:
    using XMLException::XMLException; 
};

/**
 * Excepción que hereda de XMLException, para cunado haya un fallo al parsear el archivo
*/
class XMLParseException : public XMLException {
public:
    using XMLException::XMLException; 
};

/**
 * Excepción que hereda de XMLException, para cuando falle la búsqueda de un elemento concreto
*/
class XMLElementNotFoundException : public XMLException {
public:
    using XMLException::XMLException; 
};

/**
 * TODO: Clase que agrupe cualquier tipo de dato
 * para desacoplar más el código, ya que funciones no
 * devuelven solo primitivos
*/
class XMLData {

};

/**
 * Clase que representa un atributo de un elemento XML. Tiene dos string privados
 * que representan el nombre y el valor del atributo.
*/
class XMLAtributo {

private:
    // Nombre del atributo
    string name;
    // Cadena con el valor del atributo
    string valor;

public:
    // Constructor vacío
    XMLAtributo();
    // Constructor que inicializa los atributos
    XMLAtributo(string name, string valor);
    
    string getName() const;
    string getValor() const;

    string toString() const;
    
};

/**
 * Clase que representa un elemento del fichero XML. Tiene cadenas que 
 * representan el nombre y el valor del elemento, si lo tuviese. Además,
 * tiene dos colecciones, un es vector<XMLAtributo> que representa los
 * atributos del elemento, y otro vector<XMLElemento> que representa los
 * hijos que pueda tener el elemento.
 * 
 * TODO: Implementar relaciones padre-hijo entre elementos de alguna manera
*/
class XMLElemento {

private:
    vector<XMLAtributo> attributes;
    vector<XMLElemento> elements;
    string name;
    string content;
    void addSubelemento(XMLElemento e);


public:
    XMLElemento();
    XMLElemento(string name, string content, vector<XMLAtributo> atributos, vector<XMLElemento> elements);

    string getName() const;
    string getContent() const;
    vector<XMLAtributo> getAtributos();
    vector<XMLElemento> getElementos();

    string getAtributoValue(string name);
    XMLElemento getSubelement(string name);
    int numSubelements() const;
    string toString() const;
};

/**
 * Clase que representa el documento XML a leer. Tiene como atributos
 * el path al xml y al dtd (TODO: IMPLEMENTAR DTD PARSER, BUSCAR ALTERNATIVA
 * A TINYXML2). Tiene el elemento raíz como atributo privado, y es en esta
 * clase donde se implementa la funcionalidad de la librería externa.
*/
class XMLDoc {

private:
    char * xmlPath;
    char * dtdPath;
    XMLElemento rootElement;

    XMLElemento parseElement(const tinyxml2::XMLElement* e);

public:
    // XMLDoc(string xmlPath, string dtdPath, XMLElemento rootElement);
    XMLDoc(char * xmlPath);
    XMLDoc();

    ~XMLDoc();

    char * getXmlPath() const;
    char * getDtdPath() const;
    XMLElemento getRootElement() const;

    string toString() const;

};

#endif