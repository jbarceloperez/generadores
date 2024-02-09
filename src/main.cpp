#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <filesystem>

#include "tinyxml2.h"   // no parsea dtds, no habria que usar esta libreria

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
        return 1;
    }

    const XMLElement* filesElement = doc.FirstChildElement("files");
    if (!filesElement) {
        std::cerr << "Missing <files> element in XML file." << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, std::string>> fileContents;

    const XMLElement* fileElement = filesElement->FirstChildElement("file");
    while (fileElement) {
        const XMLElement* nameElement = fileElement->FirstChildElement("name");
        const XMLElement* extensionElement = fileElement->FirstChildElement("extension");
        const XMLElement* contentElement = fileElement->FirstChildElement("content");

        if (!nameElement || !contentElement || !extensionElement) {
            std::cerr << "Malformed <file> element in XML file." << std::endl;
            return 1;
        }

        const char* name = nameElement->GetText();
        const char* content = contentElement->GetText();
        const char* ext = extensionElement->GetText();

        fileContents.push_back(std::make_pair(std::string(name), std::string(content)));

        fileElement = fileElement->NextSiblingElement("file");
    }

    std::string path("./out");
    //std::strcat(path, "./out");
    std::filesystem::create_directory(path);

    for (const auto& fileContent : fileContents) {
        std::ofstream outputFile(fileContent.first);
        if (!outputFile) {
            std::cerr << "Error creating file: " << fileContent.first << std::endl;
            return 1;
        }
        outputFile << fileContent.second;
        std::cout << "File created: " << fileContent.first << std::endl;
    }

    return 0;
}
