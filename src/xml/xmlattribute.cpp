#include "xmlattribute.h"

// ----------------------------------------------------------------------
//  XMLAttribute
// ----------------------------------------------------------------------

XMLAttribute::XMLAttribute(std::string name, std::string valor) : name(name), valor(valor) {}

std::string XMLAttribute::getName() const {
    return name;
}

std::string XMLAttribute::getValor() const {
    return valor;
}

std::string XMLAttribute::toString() const
{
    return std::string("XMLAributo: [" + name + "] -> " + valor + "\n");
}
