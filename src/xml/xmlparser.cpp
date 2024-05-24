#include "xmlparser.h"

#include <iostream>
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
    std::cerr << e.toString(0);    // DEBUG
    return e;
}

/**
 * Escribe con formato XML los paneles existentes en panels en el
 * fichero input.xml, implementa funcionalidad de la libreria externa.
*/
void writeXMLFile(PanelCollection panels)
{
    // tinyxml2::XMLDocument doc;
    
    // tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
    // doc.InsertFirstChild(decl);
    
    // // root element <panels>
    // tinyxml2::XMLElement* root = doc.NewElement("panels");
    // doc.InsertEndChild(root);

    // // insertar cada panel
    // for (GPanel p : panels.getVector())
    // {
    //     tinyxml2::XMLElement* panel = doc.NewElement("panel");
        
    //     panel->SetAttribute("name",p.getName().data());
    //     panel->SetAttribute("type",PanelTypeToString[p.getType()].data());
    //     root->InsertEndChild(panel);

    //     // añadir su layout si no es el default
    //     if (p.getLayout()!=DEFAULT_LAYOUT)
    //     {
    //         tinyxml2::XMLElement* layout = doc.NewElement("layout");
    //         layout->SetText(LayoutTypeToString[p.getLayout()].data());
    //         panel->InsertEndChild(layout);
    //     }
        
    //     // añadir el tamaño si no es el default
    //     if (p.getHeight()!=DEFAULT_H || p.getWidth()!=DEFAULT_W)
    //     {
    //         tinyxml2::XMLElement* geometry = doc.NewElement("geometry");
    //         tinyxml2::XMLElement* height = doc.NewElement("h");
    //         tinyxml2::XMLElement* width = doc.NewElement("w");
    //         height->SetText(p.getHeight());
    //         width->SetText(p.getWidth());
    //         geometry->InsertEndChild(height);
    //         geometry->InsertEndChild(width);
    //         panel->InsertEndChild(geometry);
    //     }

    //     PanelType tipo = p.getType();
    //     // si es de tipo ui externo, añadir el path del ui
    //     if (tipo == EXTERNAL_UI_CONFIG || tipo == EXTERNAL_UI_READ)
    //     {
    //         tinyxml2::XMLElement* uipath = doc.NewElement("uipath");
    //         uipath->SetText(p.getUiPath().data());
    //         panel->InsertEndChild(uipath);
    //     }
    //     // si es de tipo config, añadir los botones
    //     if (tipo == EXTERNAL_UI_CONFIG || tipo == CONFIG)
    //     {
    //         tinyxml2::XMLElement* buttonsElement = doc.NewElement("buttons");
    //         panel->InsertEndChild(buttonsElement);
    //         for (Button b : p.getButtons())
    //         {
    //             tinyxml2::XMLElement* button = doc.NewElement("button");
    //             button->SetAttribute("type",ButtonTypeToString[b.getType()].data());
    //             buttonsElement->InsertEndChild(button);
                
    //             tinyxml2::XMLElement* name = doc.NewElement("name");
    //             name->SetText(b.getName().data());
    //             button->InsertEndChild(name);
    //             if (b.getAction() != NULLBUTTONACTION)
    //             {
    //                 tinyxml2::XMLElement* action = doc.NewElement("action");
    //                 action->SetText(ButtonActionToString[b.getAction()].data());
    //                 button->InsertEndChild(action);
    //             }
    //         }
    //     }
    //     // TODO: continuar con condiciones, si no tiene ui, más elementos, etc.
    // }
    
    // // guardar el documento
    // if (doc.SaveFile(xmlPath) == tinyxml2::XML_SUCCESS) {
    //     Controller::getInstance().printTrace(INFO, "XMLFile succesfully saved in " + std::string(xmlPath));
    // } else {
    //     Controller::getInstance().printTrace(ERROR, "Error saving file:" + std::string(xmlPath));        
    // }
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
