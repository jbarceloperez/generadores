#ifndef XMLATTRIBUTE_H
#define XMLATTRIBUTE_H

#include <string>

/**
 * Clase que representa un atributo de un elemento XML. Tiene dos string privados
 * que representan el nombre y el valor del atributo.
*/
class XMLAttribute {

private:
    // Nombre del atributo
    std::string name;
    // Cadena con el valor del atributo
    std::string valor;

public:
    XMLAttribute() {};
    // Constructor que inicializa los atributos
    XMLAttribute(std::string name, std::string valor);
    
    std::string getName() const;
    std::string getValor() const;

    std::string toString() const;
    
};

#endif