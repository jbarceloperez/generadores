#include "generador.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>    // for using transform 
#include <cctype>       // for using toUpper
#include <cstdio>       // sprintf

#include "templatefunctions.cpp"

namespace fs = std::filesystem;
using namespace std;


/**
 * Función que genera la estructura de ficheros para
 * la estructura de clases del panel.
*/
void generatePanelFiles(GPanel p)
{
    map<TemplateMark, string> properties;
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

    if (p.getType() == PanelType::CONFIG || p.getType() == PanelType::READ_ONLY)
    {
        // Archivo Panel.ui, si no existe previamente
        fs::path panelUiPath = aux_root + ".ui";
        ofstream outUi(panelUiPath);
        outUi << writeFile(p, properties, UI);
        cout << "Creado nuevo fichero -> " << panelUiPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes
    }
}

//-----------------------------------------------------------------------------

void fillPropertiesMap(GPanel p, map<TemplateMark, string>& props) {
    for (int m = NAME; m < END_MARK; m++)
    {
        props[static_cast<TemplateMark>(m)] = "";
    }
    props[NAME] = p.getName();
    string str = p.getName();
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    props[NAME_CAPS] = str;
    for (Button b : p.getButtons())
    {
        if (b.getAction()==APPLY)
        {
            props[PANEL_APPLY_H] = Functions[PANEL_APPLY_H];
            char buff[200];
            string aux = Functions[PANEL_APPLY_CPP];
            sprintf(buff, aux.data(), p.getName().data());
            props[PANEL_APPLY_CPP] = buff;
            aux = Functions[ADD_FOOTER_BUTTON_APPLY];
            sprintf(buff, aux.data(), b.getName().data());
            props[ADD_FOOTER_BUTTON_APPLY] = buff;
        }
        else if(b.getAction()==CANCEL)
        {
            props[PANEL_CANCEL_H] = Functions[PANEL_CANCEL_H];
            char buff[200];
            string aux = Functions[PANEL_CANCEL_CPP];
            sprintf(buff, aux.data(), p.getName().data());
            props[PANEL_CANCEL_CPP] = buff;
            aux = Functions[ADD_FOOTER_BUTTON_CANCEL];
            sprintf(buff, aux.data(), b.getName().data());
            props[ADD_FOOTER_BUTTON_CANCEL] = buff;
        }
        else if(b.getAction()==CHECK)
        {
            props[PANEL_CHECK_H] = Functions[PANEL_CHECK_H];
            char buff[200];
            string aux = Functions[PANEL_CHECK_CPP];
            sprintf(buff, aux.data(), p.getName().data());
            props[PANEL_CHECK_CPP] = buff;
            aux = Functions[ADD_FOOTER_BUTTON_CHECK];
            sprintf(buff, aux.data(), b.getName().data());
            props[ADD_FOOTER_BUTTON_CHECK] = buff;
        }
        else if(b.getAction()==RESET)
        {
            props[PANEL_RESET_H] = Functions[PANEL_RESET_H];
            char buff[200];
            string aux = Functions[PANEL_RESET_CPP];
            sprintf(buff, aux.data(), p.getName().data());
            props[PANEL_RESET_CPP] = buff;
            aux = Functions[ADD_FOOTER_BUTTON_RESET];
            sprintf(buff, aux.data(), b.getName().data());
            props[ADD_FOOTER_BUTTON_RESET] = buff;
        }
        else if(b.getAction()==CUSTOM1)
        {
            props[PANEL_CUSTOM1_H] = Functions[PANEL_CUSTOM1_H];
            char buff[200];
            string aux = Functions[PANEL_CUSTOM1_CPP];
            sprintf(buff, aux.data(), p.getName().data());
            props[PANEL_CUSTOM1_CPP] = buff;
            aux = Functions[ADD_FOOTER_BUTTON_CUSTOM1];
            sprintf(buff, aux.data(), b.getName().data());
            props[ADD_FOOTER_BUTTON_CUSTOM1] = buff;
        }
        else if(b.getAction()==CUSTOM2)
        {
            props[PANEL_CUSTOM2_H] = Functions[PANEL_CUSTOM2_H];
            char buff[200];
            string aux = Functions[PANEL_CUSTOM2_CPP];
            sprintf(buff, aux.data(), p.getName().data());
            props[PANEL_CUSTOM2_CPP] = buff;
            aux = Functions[ADD_FOOTER_BUTTON_CUSTOM2];
            sprintf(buff, aux.data(), b.getName().data());
            props[ADD_FOOTER_BUTTON_CUSTOM2] = buff;
        }
    }
}   



string writeFile(GPanel p, map<TemplateMark, string>& properties, FileToGenerate file)
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

void replaceMarks(string &code, const map<TemplateMark, string> &props)
{
    for (const auto& pair : props) {
        std::string placeholder = "%" + MarkStrings.find(pair.first)->second + "%";
        size_t pos = code.find(placeholder);
        while (pos != std::string::npos) {
            code.replace(pos, placeholder.size(), pair.second);
            pos = code.find(placeholder);
        }
    }
}

