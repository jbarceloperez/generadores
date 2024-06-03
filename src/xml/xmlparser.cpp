#include "xmlparser.h"

#include "../controller.h"


XMLElement XMLParser::readXml(char *xmlPath)
{
    QFile file(xmlPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw XMLFileException("Error al abrir el archivo XML.");
    }

    QXmlStreamReader xmlReader(&file);
    xmlReader.readNextStartElement();
    XMLElement e = parseElement(xmlReader);
    return e;
}


/**
 * Implementa la funcionalidad de la librería externa. Rellena el objeto XMLFile
 * con los elementos y atributos correspondientes que va creando a medida que
 * el QXmlStreamReader de Qt va parseando el documento.
*/
XMLElement XMLParser::parseElement(QXmlStreamReader& xmlReader) {

    // nombre y atributos del elemento
    QString name = xmlReader.name().toString();
    
    // procesa los atributos
    vector<XMLAttribute> atributos;
    const QXmlStreamAttributes xmlAttributes = xmlReader.attributes();
    for (const QXmlStreamAttribute& attr : xmlAttributes)   // lista de atributos
    {
        atributos.push_back(XMLAttribute(attr.name().toString().toStdString(), attr.value().toString().toStdString()));
    }

    QString content("");    // cadena del contenido del elemento

    // de forma recursiva va parseando texto y subelementos
    vector<XMLElement> subelementos;
    while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == name)) {
        xmlReader.readNext();
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement) 
        {   // si el token es un inicio de elemento, procesa el subelemento
            subelementos.push_back(parseElement(xmlReader));
        } 
        else if (xmlReader.tokenType() == QXmlStreamReader::Characters && !xmlReader.isWhitespace()) 
        {   // si el token es caracteres, procesa el contenido del elemento
            content = xmlReader.text().toString();
        }
    }

    // cuando tiene todo parseado devuelve el elemento a la función anterior
    
    return XMLElement(name.toStdString(), content.toStdString(), atributos, subelementos);
}

/**
 * Escribe con formato XML los paneles existentes en panels en el
 * fichero input.xml, implementa funcionalidad de la libreria externa.
*/
void XMLParser::writeXMLFile(PanelCollection panels, string xmlPath)
{
    QFile file(xmlPath.data());
    if (!file.open(QIODevice::WriteOnly)) {
        Controller::getInstance().printTrace(ERROR, "Error opening file:" + std::string(xmlPath));
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    
    // root element <panels>
    xmlWriter.writeStartElement("panels");  // <panels>

    // insertar cada panel
    for (GPanel p : panels.getVector())
    {
        xmlWriter.writeStartElement("panel");   // <panel>
        
        xmlWriter.writeAttribute("name", QString::fromStdString(p.getName()));
        xmlWriter.writeAttribute("type", QString::fromStdString(PanelTypeToString[p.getType()]));

        // añadir header
        xmlWriter.writeStartElement("header");  // <header>
        for (int i=0; i < HeaderElement::NOELEMENTS; i++)
        {
            HeaderElement he = static_cast<HeaderElement>(i);
            if (p.getHeaderElement(he).compare("")) // si no está vacio, escribe el header
            {
                xmlWriter.writeStartElement(QString::fromStdString(HeaderElementXMLMap[he]));  // <headerElement>
                xmlWriter.writeCharacters(QString::fromStdString(p.getHeaderElement(he)));
                xmlWriter.writeEndElement();    // </headerElement>
            }
        }
        xmlWriter.writeEndElement(); // </header>
        


        // añadir su layout si no es el default
        if (p.getLayout()!=DEFAULT_LAYOUT)
        {
            xmlWriter.writeStartElement("layout");  // <layout>
            xmlWriter.writeCharacters(QString::fromStdString(LayoutTypeToString[p.getLayout()]));
            xmlWriter.writeEndElement(); // </layout>
        }
        
        // añadir el tamaño si no es el default
        if (p.getHeight()!=DEFAULT_H || p.getWidth()!=DEFAULT_W)
        {
            xmlWriter.writeStartElement("geometry");    // <geometry>
            xmlWriter.writeTextElement("h", QString::number(p.getHeight()));
            xmlWriter.writeTextElement("w", QString::number(p.getWidth()));
            xmlWriter.writeEndElement(); // </geometry>
        }

        PanelType tipo = p.getType();
        // si es de tipo ui externo, añadir el path del ui
        if (tipo == EXTERNAL_UI_CONFIG || tipo == EXTERNAL_UI_READ)
        {
            xmlWriter.writeStartElement("uipath");  // <uipath>
            xmlWriter.writeCharacters(QString::fromStdString(p.getUiPath()));
            xmlWriter.writeEndElement(); // </uipath>
        }
        // si es de tipo config, añadir los botones
        if (tipo == EXTERNAL_UI_CONFIG || tipo == CONFIG)
        {
            xmlWriter.writeStartElement("buttons"); // <buttons>

            for (Button b : p.getButtons())
            {
                xmlWriter.writeStartElement("button");  // <button>
                xmlWriter.writeAttribute("type", QString::fromStdString(ButtonTypeToString[b.getType()]));
                xmlWriter.writeTextElement("name", QString::fromStdString(b.getName()));
                if (b.getAction() != NULLBUTTONACTION)
                {
                    xmlWriter.writeTextElement("action", QString::fromStdString(ButtonActionToString[b.getAction()]));
                }
                xmlWriter.writeEndElement(); // </button>
            }
            xmlWriter.writeEndElement(); // </buttons>
        }
        xmlWriter.writeEndElement(); // </panel>
    }
    xmlWriter.writeEndElement();    // </panels>
    xmlWriter.writeEndDocument();

    // guardar el documento
    file.close();
    if (file.error() == QFile::NoError) 
    {
        Controller::getInstance().printTrace(INFO, "XMLFile successfully saved in " + std::string(xmlPath));
    } 
    else 
    {
        Controller::getInstance().printTrace(ERROR, "Error saving file:" + std::string(xmlPath));        
    }
}
