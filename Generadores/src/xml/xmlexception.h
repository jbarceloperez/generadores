#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

#include <exception>

/**
 * Tipo de excepción genérico para el código del wrapper.
*/
class XMLBaseException : public std::exception {
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

#endif