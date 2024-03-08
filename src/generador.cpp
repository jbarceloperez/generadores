#include "generador.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

/**
 * Función que genera la estructura de ficheros para
 * la estructura de clases del panel.
*/
void generateFiles(Panel p)
{
    string nombre = p.getName();
    fs::path folderPath = nombre;

    if (fs::exists(folderPath)) {
        try {
            fs::remove_all(folderPath);
            cout << "Directorio ./" << nombre << " ya existente. Eliminando...\n";
        } catch (const fs::filesystem_error& e) {
            cerr << "Error eliminando el directorio existente: " << e.what() << endl;
            exit(EXIT_FAILURE);
        }
    }

    fs::create_directory(folderPath);
    cout << "Creado nuevo directorio -> " << folderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes
    
    // CMakeLists del panel
    fs::path cmakePath = nombre + "/CMakeLists.txt";
    ofstream outCmakeLists(cmakePath);
    outCmakeLists << writeCmake(p);    
    cout << "Creado nuevo fichero -> " << cmakePath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Carpeta con los ficheros del panel
    fs::path srcDirPath = nombre + "/src_inc";
    fs::create_directory(srcDirPath);
    cout << "Creado nuevo directorio -> " << srcDirPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    string aux_root = nombre + "/src_inc/" + nombre;

    // Archivo panel.h
    fs::path panelHeaderPath = aux_root + ".h";
    ofstream outHeader(panelHeaderPath);
    outHeader << "// " + panelHeaderPath.string();
    cout << "Creado nuevo fichero -> " << panelHeaderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelGw.h
    fs::path panelGwHeaderPath = aux_root + "Gw.h";
    ofstream outGwHeader(panelGwHeaderPath);
    outGwHeader << "// " + panelGwHeaderPath.string();
    cout << "Creado nuevo fichero -> " << panelGwHeaderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelGw.cpp
    fs::path panelGwPath = aux_root + "Gw.cpp";
    ofstream outGw(panelGwPath);
    outGw << "// " + panelGwPath.string();
    cout << "Creado nuevo fichero -> " << panelGwPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelQtCb.h
    fs::path panelQtCbHeaderPath = aux_root + "QtCb.h";
    ofstream outQtCbHeader(panelQtCbHeaderPath);
    outQtCbHeader << "// " + panelQtCbHeaderPath.string();
    cout << "Creado nuevo fichero -> " << panelQtCbHeaderPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    // Archivo PanelQtCb.cpp
    fs::path panelQtCbPath = aux_root + "QtCb.cpp";
    ofstream outQtCb(panelQtCbPath);
    outQtCb << "// " + panelQtCbPath.string();
    cout << "Creado nuevo fichero -> " << panelQtCbPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

    
}

void generateFilesWithUi(Panel p)
{
    generateFiles(p);

    // Archivo Panel.ui, si no existe previamente
    fs::path panelUiPath = p.getName() + "/src_inc/" + p.getName() + ".ui";
    ofstream outUi(panelUiPath);
    outUi << writeCmake(p);
    cout << "Creado nuevo fichero -> " << panelUiPath.string() << endl;   // TODO: Cambiar esto por logs de la libreria de saes

}

//-----------------------------------------------------------------------------

string writeCmake(Panel p)
{
    string out;
    out += "#" + p.getName() + "\n";
    out += "target_sources(proj_name PRIVATE\n";
    out += "\tscr_inc/" + p.getName() + ".h\n";
    out += "\tscr_inc/" + p.getName() + "Gw.h\n";
    out += "\tscr_inc/" + p.getName() + "Gw.cpp\n";
    out += "\tscr_inc/" + p.getName() + "QtCb.h\n";
    out += "\tscr_inc/" + p.getName() + "QtCb.cpp\n)\n\n";
    out += "target_include_directories(proj_name PRIVATE src_inc)\n";
    return out;
}
