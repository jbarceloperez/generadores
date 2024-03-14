#include "generador.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <map>
#include <algorithm> // for using transform 
#include <cctype> // for using toupper

namespace fs = std::filesystem;
using namespace std;


/**
 * Función que genera la estructura de ficheros para
 * la estructura de clases del panel.
*/
void generateFiles(Panel p)
{
    map<string, string> properties;
    fillPropertiesMap(p, properties);

    string name = p.getName();
    fs::path folderPath = name;

    if (fs::exists(folderPath)) {
        try {
            fs::remove_all(folderPath);
            cout << "Directorio ./" << name << " ya existente. Eliminando...\n";
        } catch (const fs::filesystem_error& e) {
            cerr << "Error eliminando el directorio existente: " << e.what() << endl;
            exit(EXIT_FAILURE);
        }
    }

    fs::create_directory(folderPath);
    cout << "Creado nuevo directorio -> " << folderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes
    
    // Carpeta con los ficheros del panel
    fs::path srcDirPath = name + "/src_inc";
    fs::create_directory(srcDirPath);
    cout << "Creado nuevo directorio -> " << srcDirPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    string aux_root = name + "/src_inc/" + name;

     // CMakeLists del panel
    fs::path cmakePath = name + "/CMakeLists.txt";
    ofstream outCmakeLists(cmakePath);
    outCmakeLists << writeFile(p, properties, CMAKELISTS);    
    cout << "Creado nuevo fichero -> " << cmakePath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo panel.h
    fs::path panelHeaderPath = aux_root + ".h";
    ofstream outHeader(panelHeaderPath);
    // outHeader << "// " + panelHeaderPath.string();
    outHeader << writeFile(p, properties, HEADER);
    cout << "Creado nuevo fichero -> " << panelHeaderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelGw.h
    fs::path panelGwHeaderPath = aux_root + "Gw.h";
    ofstream outGwHeader(panelGwHeaderPath);
    outGwHeader << writeFile(p, properties, GWHEADER);
    cout << "Creado nuevo fichero -> " << panelGwHeaderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelGw.cpp
    fs::path panelGwPath = aux_root + "Gw.cpp";
    ofstream outGw(panelGwPath);
    outGw << writeFile(p, properties, GW);
    cout << "Creado nuevo fichero -> " << panelGwPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelQtCb.h
    fs::path panelQtCbHeaderPath = aux_root + "QtCb.h";
    ofstream outQtCbHeader(panelQtCbHeaderPath);
    outQtCbHeader << writeFile(p, properties, QTCBHEADER);
    cout << "Creado nuevo fichero -> " << panelQtCbHeaderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelQtCb.cpp
    fs::path panelQtCbPath = aux_root + "QtCb.cpp";
    ofstream outQtCb(panelQtCbPath);
    outQtCb << writeFile(p, properties, QTCB);
    cout << "Creado nuevo fichero -> " << panelQtCbPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo Panel.ui, si no existe previamente
    fs::path panelUiPath = aux_root + ".ui";
    ofstream outUi(panelUiPath);
    outUi << writeFile(p, properties, UI);
    cout << "Creado nuevo fichero -> " << panelUiPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    
}

//-----------------------------------------------------------------------------

void fillPropertiesMap(Panel p, map<string, string>& props) {
    props["NAME"] = p.getName();
    string str = p.getName();
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    props["NAME_CAPS"] = str;
}   



string writeFile(Panel p, map<string, string>& properties, FileToGenerate file)
{   
    string code;

    switch (file)
    {
    case HEADER:
        code = readTemplate("../templates/Header.template");
        break;
    case GWHEADER:
        code = readTemplate("../templates/GwHeader.template");
        break;
    case GW:
        code = readTemplate("../templates/Gw.template");
        break;
    case QTCBHEADER:
        code = readTemplate("../templates/QtCbHeader.template");
        break;
    case QTCB:
        code = readTemplate("../templates/QtCb.template");
        break;
    case CMAKELISTS:
        code = readTemplate("../templates/CMakeLists.template");
        break;
    case UI:
        code = readTemplate("../templates/Ui.template");
        break;
    default:
        // unreachable
        exit(EXIT_FAILURE);
    }

    replaceMarks(code, properties);
    return code;
}

string readTemplate(const std::string &filename)
{
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void replaceMarks(string &code, const map<string, string> &props)
{
    for (const auto& pair : props) {
        std::string placeholder = "%" + pair.first + "%";
        size_t pos = code.find(placeholder);
        while (pos != std::string::npos) {
            code.replace(pos, placeholder.size(), pair.second);
            pos = code.find(placeholder);
        }
    }
}

