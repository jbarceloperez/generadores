#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include "panel.cpp"

#include "tinyxml2.h"   // no parsea dtds, no habria que usar esta libreria

#define MYNULL -1

using namespace tinyxml2;

int main(int argc, char* argv[]) 
{

    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " input.xml" << std::endl;
        return EXIT_FAILURE;
    }

    const char* inputFileName = argv[1];

    //

    XMLDocument doc;
    if (doc.LoadFile(inputFileName) != XML_SUCCESS) {
        std::cerr << "Error loading XML file: " << inputFileName << std::endl;
        return EXIT_FAILURE;
    }

    const XMLElement* panelsElement = doc.FirstChildElement("panels");
    if (!panelsElement) {
        std::cerr << "Missing <panels> element in XML file." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<Panel> panelContents;

    // Aquí comienza a detectar paneles a generar

    const XMLElement* panelElement = panelsElement->FirstChildElement("panel");
    while (panelElement) {
        const XMLAttribute* typeAttribute = panelElement->FindAttribute("type");
        bool fixed = strcmp(typeAttribute->Value(), "fixed") ? true : false;

        const XMLElement* nameElement = panelElement->FirstChildElement("name");

        if (!nameElement) {
            std::cerr << "Malformed <panel> element in XML file (no name)." << std::endl;
            return EXIT_FAILURE;
        }

        const char* name = nameElement->GetText();

        const XMLElement* xElement = panelElement->FirstChildElement("x");
        const XMLElement* yElement = panelElement->FirstChildElement("y");
        const XMLElement* wElement = panelElement->FirstChildElement("w");
        const XMLElement* hElement = panelElement->FirstChildElement("h");

        int x = xElement ? atoi(xElement->GetText()) : MYNULL;
        int y = yElement ? atoi(yElement->GetText()) : MYNULL;
        int w = wElement ? atoi(wElement->GetText()) : MYNULL;
        int h = hElement ? atoi(hElement->GetText()) : MYNULL;
        
        panelContents.push_back(Panel(name, x, y, w, h, fixed));

        panelElement = panelElement->NextSiblingElement("panel");
    }

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
