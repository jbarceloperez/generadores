#include "xmlattribute.h"

// ----------------------------------------------------------------------
//  XMLAttribute
// ----------------------------------------------------------------------

XMLAttribute::XMLAttribute(std::string name, std::string value) : name(name), value(value) {}

std::string XMLAttribute::getName() const {
    return name;
}

std::string XMLAttribute::getValue() const {
    return value;
}

std::string XMLAttribute::toString() const
{
    return std::string("XMLAributo: [" + name + "] -> " + value + "\n");
}
