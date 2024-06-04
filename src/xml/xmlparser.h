#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <vector>
#include "../model/gpanel.h"
#include "../model/panelcollection.h"
#include "xmlattribute.h"
#include "xmlelement.h"
#include "xmlfile.h"
#include "xmlexception.h"

// Librería externa para wrappear las clases XML
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>
#include <QString>

using namespace std;

/**
 * Clase con la funcionalidad para leer y escribir ficheros XML. Implementa
 * funcionalidad de la librería externa (Qt) para esta funcionalidad.
*/
class XMLParser {

public:
    XMLParser() {};
    XMLElement readXml(char *path);
    XMLElement parseElement(QXmlStreamReader& xml);
    void writeXMLFile(PanelCollection panels, string xmlPath);
    GPanel buildPanel(XMLElement e);
};

#endif
