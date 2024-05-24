#include "xmlfile.h"
#include "xmlparser.h"

// ----------------------------------------------------------------------
//  XMLFile
// ----------------------------------------------------------------------

/**
 * Desde el constructor se carga el documento XML con la librería externa
 * y se parsea como un elemento XMLFile con sus respectivos subelementos.
*/
XMLFile::XMLFile(char* _xmlPath) {
    xmlPath = _xmlPath;
}

void XMLFile::read()
{
    XMLParser parser;
    rootElement = parser.readXml(xmlPath);
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
