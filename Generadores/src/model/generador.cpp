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

Generador::Generador()
{
    log = Controller::getInstance().getLogger();
}

/**
 * Función que genera la estructura de ficheros para
 * la estructura de clases del panel. Es como el main del generador
*/
void Generador::generatePanelFiles(GPanel p, string outDirectory)
{
    map<TemplateMark, string> properties = fillPropertiesMap(p);
    map<string, string> documentation = readDocumentation(FULLPATH("Documentation.txt"));

    string dirPath = outDirectory + "/" + p.getName();  // ruta absoluta al directorio
    string aux_root = dirPath + "/src_inc/" + p.getName(); // prefijo de cada fichero en la carpeta de sources
    string srcDirPath = dirPath + "/src_inc";       // ruta absoluta al directorio de sources
    string testsDirPath = dirPath + "/tests";     // ruta absoluta al directorio de tests

    // Verifica si el directorio ya existe
    if (fs::exists(dirPath)) {
        try {
            fs::remove_all(dirPath);
            log->mainlog(INFO, "Directorio '" + dirPath + "' ya existente. Eliminando...");
        } catch (const fs::filesystem_error& e) {
            log->mainlog(CRITICAL, "Error eliminando el directorio existente.");
            log->mainlog(CRITICAL, e.what());
            exit(EXIT_FAILURE);
        }
    }

    // Crea la carpeta donde se guardará el cmakelists y la carpeta src_inc
    fs::create_directory(dirPath);
    log->mainlog(INFO, "Creado nuevo directorio -> " + dirPath);

    // Carpeta con los ficheros del panel
    fs::create_directory(srcDirPath);
    log->mainlog(INFO, "Creado nuevo directorio -> " + srcDirPath);

    // Carpeta con los tests
    if (p.getTest())
    {
        fs::create_directory(testsDirPath);
        log->mainlog(INFO, "Creado nuevo directorio -> " + testsDirPath);
        writeFile(testsDirPath + "/test_" + p.getName() + ".cpp", documentation, properties, TESTFILE);
        writeFile(testsDirPath + "/test_main.cpp", documentation, properties, TESTMAIN);
    }
    
    // Genera todos los ficheros
    writeFile(dirPath + "/CMakeLists.txt", documentation, properties, CMAKELISTS);
    writeFile(dirPath + "/Doxyfile", documentation, properties, DOXYFILE);
    writeFile(aux_root + ".h", documentation, properties, HEADER);
    writeFile(aux_root + "Gw.h", documentation, properties, GWHEADER);
    writeFile(aux_root + "Gw.cpp", documentation, properties, GW);
    writeFile(aux_root + "QtCb.h", documentation, properties, QTCBHEADER);
    writeFile(aux_root + "QtCb.cpp", documentation, properties, QTCB);
    if (p.getType() == PanelType::CONFIG || p.getType() == PanelType::READ_ONLY)
    {
        writeFile(aux_root + ".ui", documentation, properties, UI);
    }
    else    // en caso de que el ui ya exista, se debe insertar ese el .ui en la carpeta
    {
        fs::path uiPath = p.getUiPath();
        fs::path targetDir = srcDirPath;
        auto target = targetDir / uiPath.filename();
        try
        {
            fs::copy_file(uiPath, target);
            log->mainlog(INFO, "Creado nuevo fichero -> " + aux_root + ".ui");
        }
        catch (exception& e)  
        {
            log->mainlog(CRITICAL, "Error al copiar el fichero");
            log->mainlog(CRITICAL, e.what());
        }
    }
    
}

//-----------------------------------------------------------------------------

/**
 * @brief Función que escribe en un fichero el código generado
 * @param path Ruta absoluta del fichero a escribir
 * @param documentation
 * @param properties Map con las propiedades del panel
 * @param file Tipo de fichero a escribir
 * @note
 * La función abre un ofstream al path correspondiente. 
 * Escribe el código de la plantilla correspondiente en una string mediante la
 * función readTemplate, y luego procesa ese string con la función replaceMarks.
 * Tras eso, añade la documentación al código generado.
 * Finalmente, escribe el contenido en el ofstream y lo cierra. 
*/
void Generador::writeFile(const string& path, map<string, string> &documentation, map<TemplateMark, string> &properties, FileToGenerate file)
{
    ofstream out(path); // abre el ofstream al path correspondiente
    string code;
    code = readTemplate(FileTemplatePath[file]); // lee el contenido de la plantilla a code
    replaceMarks(code, properties); // procesa la plantilla y rellena las marcas
    addDocumentation(code, documentation, properties[NAME]);  // agrega la documentación al código generado
    out << code;    // escribe el contenido en el ofstream
    log->mainlog(INFO, "Creado nuevo fichero -> " + path);
    out.close(); // cierra el ofstream
}

/**
 * @brief Función que rellena el valor de las marcas de la plantilla con las
 * propiedades del panel pasado como parámetro. 
 * @param p Objeto GPanel con las propiedades del panel
 * @return map<TemplateMark, string> con las propiedades del panel
*/
map<TemplateMark, string> Generador::fillPropertiesMap(GPanel p) 
{
    map<TemplateMark, string> props;
    for (int m = NAME; m < END_MARK; m++)   // inicializar propiedades a 0
        props[static_cast<TemplateMark>(m)] = "";
    map<TemplateMark, string> code_chunks = readCodeChunks(FULLPATH("Functions.txt"));
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
    if (p.getType() == CONFIG || p.getType() == EXTERNAL_UI_CONFIG)
    {   // si hay botones añadir el metodo panelCheck()
        string aux;
        props[PANEL_CHECK_H] = code_chunks[PANEL_CHECK_H];
        char buff[200];
        aux = code_chunks[PANEL_CHECK_CPP];
        sprintf(buff, aux.data(), p.getName().data());
        props[PANEL_CHECK_CPP] = buff;
    }

    if (p.getTest())
    {
        fillTests(p, code_chunks, props);
        string aux;
        char buff[1200];
        aux = code_chunks[TEST_CMAKE];
        const char * name = p.getName().data();
        sprintf(buff, aux.data(), name, name, name, name, name, name, name, name, name, name, name, name);
        props[TEST_CMAKE] = buff;
    }

    return props;
}

void Generador::fillTests(GPanel &p, std::map<TemplateMark, std::string> &code_chunks, std::map<TemplateMark, std::string> &props)
{
    for (GButton b : p.getButtons())
    {
        string aux = code_chunks[TEST_FUNCTION];
        char buff[400];
        sprintf(buff, aux.data(), p.getName().data(), b.getName().data(), b.getName().data());
        props[TESTS] += buff;
    }
}

void Generador::fillButtonMarks(GPanel &p, map<TemplateMark, string> &props, map<TemplateMark, string> &code_chunks)
{
    // generacion de los botones
    string str_buttons = "";
    int n_buttons = 0;
    for (GButton b : p.getButtons())
    {
        ButtonAction accion = b.getAction();
        string aux;
        char buff[200];
        switch (accion)
        {
        case OK:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_OK_H, PANEL_OK_CPP, ADD_FOOTER_BUTTON_OK);
            break;
        case APPLY:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_APPLY_H, PANEL_APPLY_CPP, ADD_FOOTER_BUTTON_APPLY);
            break;
        case CANCEL:
            setButtonData(props, code_chunks, p, b, str_buttons, PANEL_CANCEL_H, PANEL_CANCEL_CPP, ADD_FOOTER_BUTTON_CANCEL);
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
void Generador::setButtonData(map<TemplateMark, string> &props, map<TemplateMark, string> &code_chunks, GPanel &p, GButton &b, string &str_buttons, TemplateMark h_mark, TemplateMark cpp_mark, TemplateMark addButton_mark)
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

/**
 * @brief Función que lee un fichero con fragmentos del código a generar, 
 * y para cada línea llama a la función processChunkLine, que procesa la línea.
 * @param filename Nombre del fichero con los fragmentos de código
 * @return Mapa con la el código asociado a cada marca
*/
map<TemplateMark, string> Generador::readCodeChunks(const string &filename)
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
            processChunkLine(line, inChunk, currentChunk, codeChunks, currentCode);
        }
        file.close();
    } else {
        log->mainlog(CRITICAL, "Unable to open file");
    }
    return codeChunks;
}

/**
 * @brief Función que procesa una línea del fichero con fragmentos de código
 * y asocia cada marca con su fragmento de código.
 * @param line string con la línea a procesar
 * @param inChunk booleano que indica si actualmente se está leyendo o no un chunk
 * @param currentChunk string con el nombre de la marca del chunk actual
 * @param codeChunks mapa con las asociaciones marca-códigof
 * @param currentCode stringstream con el código actual
*/
void Generador::processChunkLine(string &line, bool &inChunk, string &currentChunk, map<TemplateMark, string> &codeChunks, ostringstream &currentCode)
{
    // se encuentra un caracter %
    if (line.find("%%") != string::npos)   // ¿es una marca de incio de code chunk?
    {
        // Comienza el code chunk
        size_t name_end = line.find('%', 2);    // busca el fin de la marca
        currentChunk = line.substr(2, name_end - 2); // obtiene el nombre del chunk
        inChunk = true;
    }
    else if (line.find("%/") != string::npos)  // ¿es una marca de fin de code chunk?
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
    else if (inChunk) { // si no es ninguna y se está leyendo un chunk, agrega la linea al stream
        currentCode << line << "\n"; 
    }
}

/**
 * @brief Función que lee un fichero con la documentación del código a generar, 
 * y para cada línea llama a la función processDocLine, que procesa la línea.
 * @param filename Nombre del fichero con la documentación
 * @return Mapa con la documentación asociada a cada marca
*/
map<string, string> Generador::readDocumentation(const string &filename)
{
    map<string, string> documentation;
    ifstream file(filename);
    string line;
    string currentChunk;
    ostringstream currentDoc;
    bool inChunk = false;

    if (file.is_open()) 
    {
        while (getline(file, line)) 
        {
            processDocLine(line, inChunk, currentChunk, documentation, currentDoc);
        }
        file.close();
    } else {
        log->mainlog(CRITICAL, "Unable to open file");
    }
    return documentation;
}

/**
 * @brief Función que procesa una línea del fichero con documentación del código
 * y asocia cada marca con su fragmento de documentación.
 * @param line string con la línea a procesar
 * @param inChunk booleano que indica si actualmente se está leyendo o no un chunk
 * @param currentChunk string con el nombre de la marca del chunk actual
 * @param documentation mapa con las asociaciones marca-documentación
 * @param currentDoc stringstream con la documentación leída actual
*/
void Generador::processDocLine(string &line, bool &inChunk, string &currentChunk, map<string, string> &documentation, ostringstream &currentDoc)
{
    // se encuentra un caracter %
    if (line.find("%%") != string::npos)   // ¿es una marca de incio?
    {
        // Comienza el chunk
        size_t name_end = line.find('%', 2);    // busca el fin de la marca
        currentChunk = line.substr(2, name_end - 2); // obtiene el nombre del chunk
        inChunk = true;
    }
    else if (line.find("%/") != string::npos)  // ¿es una marca de fin de chunk?
    {
        if (inChunk)    // si ya estaba leyendo un chunk, lo agrega al mapa
        {
            string s = currentDoc.str();   
            s.pop_back();  // elimina el último retorno de carro
            documentation[currentChunk] = s;
            currentDoc.str("");
            currentDoc.clear();
            inChunk = false;
        }
    }
    else if (inChunk) { // si no es ninguna y se está leyendo un chunk, agrega la linea al stream
        currentDoc << line << "\n";
    }
}

string Generador::readTemplate(const string &filename)
{
    ifstream file(filename);
    if (file.is_open()) 
    {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        return content;
    }
    else
    {
        log->mainlog(CRITICAL, "Unable to open file");
        return "";
    }
}

/**
 * Para cada marca del conjunto props, la busca en el codigo de la plantilla.
 * Cuando la encuentra, reemplaza la marca por su valor correspondiente.  
*/
void Generador::replaceMarks(string &code, const map<TemplateMark, string> &props)
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

/**
 * Para cada marca que coincida con una entrada del mapa de documentación,
 * sustituye la marca por su valor correspondiente.
*/
void Generador::addDocumentation(string &code, const map<string, string> &documentation, string name)
{
    for (const auto& pair : documentation) {
        string placeholder = "%" + pair.first + "%";
        size_t pos = code.find(placeholder);
        while (pos != string::npos) {
            code.replace(pos, placeholder.size(), pair.second);
            pos = code.find(placeholder);
        }
    }
    // sustituye el nombre de la marca en la documentación
    string placeholder = "%NAME%";
    size_t pos = code.find(placeholder);
    while (pos != string::npos) {
        code.replace(pos, placeholder.size(), name);
        pos = code.find(placeholder);
    }
}
