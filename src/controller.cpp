#include "controller.h"

#include "model/panel.cpp"
#include "model/panelbuilder.cpp"
#include "model/generador.cpp"
#include "xml/xmlparser.cpp"
#include "logs.hpp"


void Controller::init()
{

}

void Controller::run(int argc, char *argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " [INPUT_FILE]" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Logger
    dbg::log::initialize("traces.cfg");
    // system("xclock");
    dbg::log mainlog;
    dbg::log tracks;
    tracks.info("Code generator saes initializing...\n");
    mainlog.info("Traza warning\n");

    char* inputFileName = argv[1];

    /* TODO:Detectar si la entrada es un .ui o un .xml, para poder
            directamente leer el ui y generar la estructura de clases
            a partir de este, o hace falta generar también el ui
    */
   // regex pattern("\\.ui$");
   // regex_search(string(inputFileName), pattern);

    // XML PARSER
    
    
    try
    {
        doc = XMLFile(inputFileName);
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
    
    

    // Aquí comienza a detectar paneles a generar

    for(XMLElemento panel : doc.getRootElement().getElementos()) {
        panelContents.push_back(buildPanel(panel));
    }


    // a este punto ya debería tener los paneles claros, ahora toca
    // decidir cómo los va a generar cada uno, en su subcarpeta y con
    // sus características

    for(Panel panel : panelContents)
    {
        // std::cout << panel.toString() << std::endl; // DEBUG

        generateFiles(panel);

        cout << "Ended generating files for " + panel.getName() + "\n\n";
    }
}

Panel Controller::buildPanel(XMLElemento panel)
{
    // elementos obligatorios
    string type = panel.getAtributoValue("type");
    string name = panel.getAtributoValue("name");

    Panel panelObject = Panel(name);
    panelObject.setType(type);

    // otros elementos
    for (XMLElemento e : panel.getElementos()) {
        // TRATAR CADA POSIBLE ELEMENTO QUE SE QUIERA CONTEMPLAR

        // TODO: HACER UN SWITCH-CASE CON UN ENUM DE DIFERENTES
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

    return panelObject;
}
