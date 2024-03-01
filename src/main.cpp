#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include "panel.cpp"
#include "xmlparser.cpp"

#define MYNULL -1

// using namespace tinyxml2;

// Enumerado de tipos de elemento XML, TODO implementarlo en el código
enum Elements {geometry, sample};

int main(int argc, char* argv[]) 
{

    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " input.xml" << std::endl;
        return EXIT_FAILURE;
    }

    char* inputFileName = argv[1];

    // XML PARSER
    
    XMLDoc doc;
    try
    {
        doc = XMLDoc(inputFileName);
    }
    catch(const XMLFileException& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Error loading path '" << inputFileName << "'\n";
        exit(EXIT_FAILURE);
    }
    catch(const XMLParseException& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Missing <panels> element in XML file." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::vector<Panel> panelContents;

    // Aquí comienza a detectar paneles a generar

    for(XMLElemento panel : doc.getRootElement().getElementos()) {

        // elementos obligatorios
        string type = panel.getAtributoValue("type");
        string name = panel.getAtributoValue("name");

        Panel panelObject = Panel(name);
        panelObject.setType(type);

        // otros elementos
        for (XMLElemento e : panel.getElementos()) {
            // TRATAR CADA POSIBLE ELEMENTO QUE SE QUIERA CONTEMPLAR

            // TODO HACER UN SWITCH-CASE CON UN ENUM DE DIFERENTES
            // TIPOS DE ELEMENTO XML PARA LA APLICACION

            string name = e.getName();
            if (!name.compare("geometry")) {
                try
                {
                    panelObject.setX(atoi(e.getSubelement("x").getContent().c_str()));
                    panelObject.setY(atoi(e.getSubelement("y").getContent().c_str()));
                    panelObject.setWidth(atoi(e.getSubelement("w").getContent().c_str()));
                    panelObject.setHeight(atoi(e.getSubelement("h").getContent().c_str()));
                }
                catch(const XMLElementNotFoundException e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }
        panelContents.push_back(panelObject);
    }


    // a este punto ya debería tener los paneles claros, ahora toca
    // decidir cómo los va a generar cada uno, en su subcarpeta y con
    // sus características

    for(Panel panel : panelContents)
    {
        std::cout << panel.toString() << std::endl; // DEBUG 
    }

    // for (const auto& fileContent : panelContents) {
    //     std::ofstream outputFile(fileContent.first);
    //     if (!outputFile) {
    //         std::cerr << "Error creating file: " << fileContent.first << std::endl;
    //         return 1;
    //     }
    //     outputFile << fileContent.second;
    //     std::cout << "File created: " << fileContent.first << std::endl;
    // }

    return EXIT_SUCCESS;
}
