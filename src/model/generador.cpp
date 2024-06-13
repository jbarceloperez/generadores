#include "generador.h"
#include "../controller/controller.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>    // for using transform 
#include <cctype>       // for using toUpper
#include <cstdio>       // sprintf

namespace fs = std::filesystem;
using namespace std;


/**
 * Función que genera la estructura de ficheros para
 * la estructura de clases del panel. Es como el main del generador
*/
void generatePanelFiles(GPanel p, string outDirectory)
{
    map<TemplateMark, string> properties;
    fillPropertiesMap(p, properties);

    string dirPath = outDirectory + "/" + p.getName();  // ruta absoluta al directorio
    string aux_root = dirPath + "/src_inc/" + p.getName(); // prefijo de cada fichero en la carpeta de sources
    string srcDirPath = dirPath + "/src_inc";   // ruta absoluta al directorio de sources

    // Verifica si el directorio ya existe
    if (fs::exists(dirPath)) {
        try {
            fs::remove_all(dirPath);
            Controller::getInstance().printTrace(INFO, "Directorio '" + dirPath + "' ya existente. Eliminando...");
        } catch (const fs::filesystem_error& e) {
            Controller::getInstance().printTrace(CRITICAL, "Error eliminando el directorio existente.");
            Controller::getInstance().printTrace(CRITICAL, e.what());
            exit(EXIT_FAILURE);
        }
    }

    // Crea la carpeta donde se guardará el cmakelists y la carpeta src_inc
    fs::create_directory(dirPath);
    Controller::getInstance().printTrace(INFO, "Creado nuevo directorio -> " + dirPath);

    // Carpeta con los ficheros del panel
    fs::create_directory(srcDirPath);
    Controller::getInstance().printTrace(INFO, "Creado nuevo directorio -> " + srcDirPath);
    
    // Genera todos los ficheros
    writeFile(dirPath + "/CMakeLists.txt", p, properties, CMAKELISTS);
    writeFile(aux_root + ".h", p, properties, HEADER);
    writeFile(aux_root + "Gw.h", p, properties, GWHEADER);
    writeFile(aux_root + "Gw.cpp", p, properties, GW);
    writeFile(aux_root + "QtCb.h", p, properties, QTCBHEADER);
    writeFile(aux_root + "QtCb.cpp", p, properties, QTCB);
    if (p.getType() == PanelType::CONFIG || p.getType() == PanelType::READ_ONLY)
    {
        writeFile(aux_root + ".ui", p, properties, UI);
    }
}

//-----------------------------------------------------------------------------

/**
 * @brief Función que escribe en un fichero el código generado
 * @param path Ruta absoluta del fichero a escribir
 * @param p Objeto GPanel con los datos del panel
 * @param properties Map con las propiedades del panel
 * @param file Tipo de fichero a escribir
 * @note
 * La función abre un ofstream al path correspondiente. 
 * Escribe el código de la plantilla correspondiente en una string mediante la
 * función readTemplate, y luego procesa ese string con la función replaceMarks.
 * Finalmente, escribe el contenido en el ofstream y lo cierra. 
*/
void writeFile(const string& path, GPanel &p, map<TemplateMark, std::string> &properties, FileToGenerate file)
{
    ofstream out(path); // abre el ofstream al path correspondiente
    string code;
    code = readTemplate(FileTemplatePath[file]); // lee el contenido de la plantilla a code
    replaceMarks(code, properties); // procesa la plantilla y rellena las marcas
    out << code;    // escribe el contenido en el ofstream
    Controller::getInstance().printTrace(INFO, "Creado nuevo fichero -> " + path);
    out.close(); // cierra el ofstream
}

void fillPropertiesMap(GPanel p, map<TemplateMark, string>& props) {
    for (int m = NAME; m < END_MARK; m++)   // inicializar propiedades a 0
        props[static_cast<TemplateMark>(m)] = "";
    map<TemplateMark, string> code_chunks = readCodeChunks("../templates/Functions.txt");
    props[NAME] = p.getName();
    string str_name = p.getName();
    transform(str_name.begin(), str_name.end(), str_name.begin(), ::toupper);
    props[NAME_CAPS] = str_name;
    props[GEOMETRY_H] = to_string(p.getHeight());
    props[GEOMETRY_W] = to_string(p.getWidth());
    props[LAYOUT_UI] = LayoutTypeToString[p.getLayout()];
    props[SAES_HEADER] = p.getHeaderString();
    for (auto &i : code_chunks) 
    {
        replaceMarks(i.second, props);
    }
    fillButtonMarks(p, props, code_chunks);
}

void fillButtonMarks(GPanel &p, map<TemplateMark, string> &props, map<TemplateMark, string> &code_chunks)
{
    // generacion de los botones
    string str_buttons = "";
    int n_buttons = 0;
    for (Button b : p.getButtons())
    {
        ButtonAction accion = b.getAction();
        string aux;
        char buff[200];
        switch (accion)
        {
        case APPLY:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_APPLY_H, PANEL_APPLY_CPP, ADD_FOOTER_BUTTON_APPLY);
            break;
        case CANCEL:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_CANCEL_H, PANEL_CANCEL_CPP, ADD_FOOTER_BUTTON_CANCEL);
            break;
        case CHECK:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_CHECK_H, PANEL_CHECK_CPP, ADD_FOOTER_BUTTON_CHECK);
            break;
        case RESET:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_RESET_H, PANEL_RESET_CPP, ADD_FOOTER_BUTTON_RESET);
            break;
        case CUSTOM1:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_CUSTOM1_H, PANEL_CUSTOM1_CPP, ADD_FOOTER_BUTTON_CUSTOM1);
            break;
        case CUSTOM2:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_CUSTOM2_H, PANEL_CUSTOM2_CPP, ADD_FOOTER_BUTTON_CUSTOM2);
            break;
        default:
            break;
        }
        // generar el texto a insertar en el .ui por botón
        if (p.getLayout() == QGRIDLAYOUT || p.getLayout() == QFORMLAYOUT)
        {
            aux = code_chunks[UIXMLBUTTON_WITHPOS];
            int row = 0, col = n_buttons;
            sprintf(buff, aux.data(), row, col, b.getName().data(), b.getName().data());
        }
        else
        {
            aux = code_chunks[UIXMLBUTTON];
            sprintf(buff, aux.data(), b.getName().data(), b.getName().data());
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
void setButtonData(map<TemplateMark, string> &props, map<TemplateMark, string> &code_chunks, GPanel &p, Button &b, string &str_buttons, TemplateMark h_mark, TemplateMark cpp_mark, TemplateMark addButton_mark)
{
    string aux;
    props[h_mark] = code_chunks[h_mark];
    char buff[200];
    aux = code_chunks[cpp_mark];
    sprintf(buff, aux.data(), p.getName().data());
    props[cpp_mark] = buff;
    aux = code_chunks[addButton_mark];
    sprintf(buff, aux.data(), b.getName().data());
    props[addButton_mark] = buff;
}

map<TemplateMark, string> readCodeChunks(const string &filename)
{
    map<TemplateMark, string> codeChunks;
    ifstream file(filename);
    string line;
    string currentChunk;
    ostringstream currentCode;
    bool inChunk = false;

    if (file.is_open()) 
    {
        while (getline(file, line)) 
        {
            processLine(line, inChunk, currentChunk, codeChunks, currentCode);
        }
        file.close();
    } else {
        cerr << "Unable to open file";
    }
    return codeChunks;
}

void processLine(std::string &line, bool &inChunk, std::string &currentChunk, std::map<TemplateMark, std::string> &codeChunks, std::ostringstream &currentCode)
{
    if (line.find('%') != std::string::npos)    // se encuentra un caracter %
    {
        if (line.find("%%") != std::string::npos)   // ¿es una marca de incio de code chunk?
        {
            // Comienza el code chunk
            size_t name_end = line.find('%', 2);
            currentChunk = line.substr(2, name_end - 2); // obtiene el nombre del chunk
            inChunk = true;
        }
        else if (line.find("%/") != std::string::npos)  // ¿es una marca de fin de code chunk?
        {
            if (inChunk)    // si ya estaba leyendo un chunk, lo agrega al mapa
            {
                for (auto &i : MarkStrings)
                {
                    if (i.second == currentChunk)
                    {
                        codeChunks[i.first] = currentCode.str();
                        break;
                    }
                }
                currentCode.str("");
                currentCode.clear();
                inChunk = false;
            }
        }
        else if (inChunk) {
            currentCode << line << "\n"; // si no es ninguna de las dos marcas de code chunk, agrega la linea al stream
        }
    }
    else if (inChunk)    // si no hay '%' y esta leyendo un chunk, lo agrega al stream
    {
        currentCode << line << "\n";
    }
}

string readTemplate(const string &filename)
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
        string placeholder = "%" + MarkStrings.find(pair.first)->second + "%";
        size_t pos = code.find(placeholder);
        while (pos != string::npos) {
            code.replace(pos, placeholder.size(), pair.second);
            pos = code.find(placeholder);
        }
    }
}

