#ifndef XMLATTRIBUTE_H
#define XMLATTRIBUTE_H

#include <string>

/**
 * Clase que representa un atributo de un elemento XML. Tiene dos string privados
 * que representan el nombre y el valor del atributo.
*/
class XMLAttribute {

private:
    std::string name;   // Nombre del atributo
    std::string value;  // Cadena con el valor del atributo

public:
    XMLAttribute() {};
    // Constructor que inicializa los atributos
    XMLAttribute(std::string name, std::string value);
    
    std::string getName() const;
    std::string getValue() const;

    std::string toString() const;
    
};

#endif