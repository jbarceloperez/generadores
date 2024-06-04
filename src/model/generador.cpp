#include "generador.h"
#include "../controller.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>    // for using transform 
#include <cctype>       // for using toUpper
#include <cstdio>       // sprintf
#include "templatefunctions.h"

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
    string aux_root = name + "/src_inc/" + name;
    string srcDirPath = name + "/src_inc";
    fs::path folderPath = name;

    if (fs::exists(folderPath)) {
        try {
            fs::remove_all(folderPath);
            Controller::getInstance().printTrace(INFO, "Directorio ./" + name + " ya existente. Eliminando...");
        } catch (const fs::filesystem_error& e) {
            Controller::getInstance().printTrace(CRITICAL, "Error eliminando el directorio existente.");
            Controller::getInstance().printTrace(CRITICAL, e.what());
            exit(EXIT_FAILURE);
        }
    }

    // Crea la carpeta donde se guardará el cmakelists y la carpeta src_inc
    fs::create_directory(folderPath);
    Controller::getInstance().printTrace(INFO, "Creado nuevo directorio -> " + folderPath.string());

    // Carpeta con los ficheros del panel
    fs::create_directory(srcDirPath);
    Controller::getInstance().printTrace(INFO, "Creado nuevo directorio -> " + srcDirPath);
    
    // Genera todos los ficheros
    writeFile(name + "/CMakeLists.txt", srcDirPath, p, properties, CMAKELISTS);
    writeFile(aux_root + ".h", srcDirPath, p, properties, HEADER);
    writeFile(aux_root + "Gw.h", srcDirPath, p, properties, GWHEADER);
    writeFile(aux_root + "Gw.cpp", srcDirPath, p, properties, GW);
    writeFile(aux_root + "QtCb.h", srcDirPath, p, properties, QTCBHEADER);
    writeFile(aux_root + "QtCb.cpp", srcDirPath, p, properties, QTCB);
    if (p.getType() == PanelType::CONFIG || p.getType() == PanelType::READ_ONLY)
    {
        writeFile(aux_root + ".ui", srcDirPath, p, properties, UI);
    }
}

//-----------------------------------------------------------------------------

void writeFile(const string& path, const string& srcDirPath, GPanel &p, std::map<TemplateMark, std::string> &properties, FileToGenerate file)
{
    ofstream out(path); // abre el ofstream al path correspondiente
    string code;
    code = readTemplate(FileTemplatePath[file]); // lee el contenido de la plantilla a code
    replaceMarks(code, properties); // procesa la plantilla y rellena las marcas
    out << code;    // escribe el contenido en el ofstream
    Controller::getInstance().printTrace(INFO, "Creado nuevo fichero -> " + srcDirPath);
}

void fillPropertiesMap(GPanel p, map<TemplateMark, string>& props) {
    for (int m = NAME; m < END_MARK; m++)   // inicializar propiedades a 0
        props[static_cast<TemplateMark>(m)] = "";
    props[NAME] = p.getName();
    string str_name = p.getName();
    transform(str_name.begin(), str_name.end(), str_name.begin(), ::toupper);
    props[NAME_CAPS] = str_name;
    props[GEOMETRY_H] = to_string(p.getHeight());
    props[GEOMETRY_W] = to_string(p.getWidth());
    props[LAYOUT_UI] = LayoutTypeToString[p.getLayout()];
    props[SAES_HEADER] = p.getHeaderString();
    // generacion de los botones
    string str_buttons = "";
    int n_buttons = 0;
    for (Button b : p.getButtons())
    {
        ButtonAction accion = b.getAction();
        string aux; char buff[200];
        switch (accion)
        {
        case APPLY:
            setButtonData(props, p, b, str_buttons, PANEL_APPLY_H, PANEL_APPLY_CPP, ADD_FOOTER_BUTTON_APPLY);
            break;
        case CANCEL:
            setButtonData(props, p, b, str_buttons, PANEL_CANCEL_H, PANEL_CANCEL_CPP, ADD_FOOTER_BUTTON_CANCEL);
            break;
        case CHECK:
            setButtonData(props, p, b, str_buttons, PANEL_CHECK_H, PANEL_CHECK_CPP, ADD_FOOTER_BUTTON_CHECK);
            break;
        case RESET:
            setButtonData(props, p, b, str_buttons, PANEL_RESET_H, PANEL_RESET_CPP, ADD_FOOTER_BUTTON_RESET);
            break;
        case CUSTOM1:
            setButtonData(props, p, b, str_buttons, PANEL_CUSTOM1_H, PANEL_CUSTOM1_CPP, ADD_FOOTER_BUTTON_CUSTOM1);
            break;
        case CUSTOM2:
            setButtonData(props, p, b, str_buttons, PANEL_CUSTOM2_H, PANEL_CUSTOM2_CPP, ADD_FOOTER_BUTTON_CUSTOM2);
            break;
        default:
            break;
        }
        // generar el texto a insertar en el .ui por botón
        if (p.getLayout() == QGRIDLAYOUT || p.getLayout() == QFORMLAYOUT)
        {
            aux = CodeSnippets[UIXMLBUTTON_WITHPOS];
            int row = 0, col = n_buttons;
            sprintf(buff, aux.data(), row, col, ButtonTypeToString[b.getType()].data(), b.getName().data(), b.getName().data());
        }
        else {
            aux = CodeSnippets[UIXMLBUTTON];
            sprintf(buff, aux.data(), ButtonTypeToString[b.getType()].data(), b.getName().data(), b.getName().data());
        }
        str_buttons += buff;
        n_buttons++;
    }
    props[BUTTONS_UI] += str_buttons;
}

/**
 * Función que genera el texto correspondiente a las acciones de los botones en los
 * archivos QtCb.cpp y QtCb.h 
*/
void setButtonData(std::map<TemplateMark, std::string> &props, GPanel &p, Button &b, std::string &str_buttons, TemplateMark mark1, TemplateMark mark2, TemplateMark mark3)
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

