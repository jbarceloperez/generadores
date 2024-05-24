#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <vector>
#include "../model/panel.h"
#include "../model/panelcollection.h"
#include "xmlattribute.h"
#include "xmlelement.h"
#include "xmlfile.h"
#include "xmlexception.h"

// Librería externa para wrappear las clases XML
#include <QXmlStreamReader>
#include <QFile>
#include <QString>

using namespace std;

class XMLParser {

public:
    XMLParser() {};
    XMLElement readXml(char *path);
    XMLElement parseElement(QXmlStreamReader& xml);
    void writeXMLFile(PanelCollection panels);
};

#endif
