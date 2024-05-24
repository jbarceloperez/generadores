#ifndef XMLFILE_H
#define XMLFILE_H

#include "xmlelement.h"

/**
 * Clase que representa el documento XML a leer. Tiene como atributos el
 * path al xml y al dtd. Tiene el elemento raíz como atributo privado.
*/
class XMLFile {

private:
    char * xmlPath;
    char * dtdPath;
    XMLElement rootElement;

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

    string toString() const;

};

#endif

