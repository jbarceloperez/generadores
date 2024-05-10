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
    string str_name = p.getName();
    transform(str_name.begin(), str_name.end(), str_name.begin(), ::toupper);
    props[NAME_CAPS] = str_name;
    props[GEOMETRY_H] = to_string(p.getHeight());
    props[GEOMETRY_W] = to_string(p.getWidth());
    string str_buttons = "";
    for (Button b : p.getButtons())
    {
        ButtonAction accion = b.getAction();
        string aux; char buff[200];
        switch (accion)
        {
        case APPLY:
            setButtonUi(props, p, b, str_buttons, PANEL_APPLY_H, PANEL_APPLY_CPP, ADD_FOOTER_BUTTON_APPLY);
            str_buttons += Buttons_XML[APPLY];
            break;

        case CANCEL:
            setButtonUi(props, p, b, str_buttons, PANEL_CANCEL_H, PANEL_CANCEL_CPP, ADD_FOOTER_BUTTON_CANCEL);
            str_buttons += Buttons_XML[CANCEL];
            break;

        case CHECK:
            setButtonUi(props, p, b, str_buttons, PANEL_CHECK_H, PANEL_CHECK_CPP, ADD_FOOTER_BUTTON_CHECK);
            str_buttons += Buttons_XML[CHECK];
            break;

        case RESET:
            setButtonUi(props, p, b, str_buttons, PANEL_RESET_H, PANEL_RESET_CPP, ADD_FOOTER_BUTTON_RESET);
            str_buttons += Buttons_XML[RESET];
            break;

        case CUSTOM1:
            setButtonUi(props, p, b, str_buttons, PANEL_CUSTOM1_H, PANEL_CUSTOM1_CPP, ADD_FOOTER_BUTTON_CUSTOM1);
            aux = Buttons_XML[CUSTOM1];
            sprintf(buff, aux.data(), ButtonTypeToString[b.getType()].data(), b.getName().data(), b.getName().data());
            str_buttons += buff;
            break;
        
        case CUSTOM2:
            setButtonUi(props, p, b, str_buttons, PANEL_CUSTOM2_H, PANEL_CUSTOM2_CPP, ADD_FOOTER_BUTTON_CUSTOM2);
            aux = Buttons_XML[CUSTOM2];
            sprintf(buff, aux.data(), ButtonTypeToString[b.getType()].data(), b.getName().data(), b.getName().data());
            str_buttons += buff;
            break;
        
        default:
            aux = Buttons_XML[NULLBUTTONACTION];
            sprintf(buff, aux.data(), ButtonTypeToString[b.getType()].data(), b.getName().data(), b.getName().data());
            str_buttons += buff;
            break;
        }
    }
    props[BUTTONS_UI] += str_buttons;
}

void setButtonUi(std::map<TemplateMark, std::string> &props, GPanel &p, Button &b, std::string &str_buttons, TemplateMark mark1, TemplateMark mark2, TemplateMark mark3)
{
    props[mark1] = Functions[mark1];
    char buff[200];
    string aux = Functions[mark2];
    sprintf(buff, aux.data(), p.getName().data());
    props[mark2] = buff;
    aux = Functions[mark3];
    sprintf(buff, aux.data(), b.getName().data());
    props[mark3] = buff;
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

/**
 * Para cada marca del conjunto props, la busca en el codigo de la plantilla.
 * Cuando la encuentra, reemplaza la marca por su valor correspondiente.  
*/
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

