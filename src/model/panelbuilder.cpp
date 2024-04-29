// #include "panelbuilder.h"
// #include <iostream>
// #include <vector>
// #include "panel.h"
// #include <string>

// #include "../xml/xmlparser.h"
// #include "../controller.h"



// Panel PanelBuilder::buildPanelFromXML(XMLElemento panel) {
//     // elementos obligatorios
//     string type, name;
//     try
//     {
//         type = panel.getAtributoValue("type");
//         name = panel.getAtributoValue("name");
//     }
//     catch(const XMLAtributeNotFoundException e)
//     {
//         std::cerr << e.what() << '\n';
//     }
    
//     Panel panelObject = Panel(name);
//     panelObject.setType(type);

//     // if (panelObject.getType() == PanelType::EXTERNAL_UI)
//     // {   
//     //     string ui_path;
//     //     try {
//     //         ui_path = panel.getSubelement("uipath").getContent();
//     //     }
//     //     catch(const std::exception& e)
//     //     {
//     //         std::cerr << "Panel type 'ui' but no <uipath> element founded.\n";
//     //         std::cerr << e.what() << '\n';
//     //         exit(EXIT_FAILURE);
//     //     }
//     //     readInputUi(panelObject, ui_path);
//     // }

//     // otros elementos
//     // else {
//         for (XMLElemento e : panel.getElementos()) {
//             // TRATAR CADA POSIBLE ELEMENTO QUE SE QUIERA CONTEMPLAR

//             // TODO: HACER UN SWITCH-CASE CON UN ENUM DE DIFERENTES
//             // TIPOS DE ELEMENTO XML PARA LA APLICACION

//             string name = e.getName();
//             if (!name.compare("geometry")) {
//                 try
//                 {
//                     panelObject.setX(atoi(e.getSubelement("x").getContent().c_str()));
//                     panelObject.setY(atoi(e.getSubelement("y").getContent().c_str()));
//                     panelObject.setWidth(atoi(e.getSubelement("w").getContent().c_str()));
//                     panelObject.setHeight(atoi(e.getSubelement("h").getContent().c_str()));
//                 }
//                 catch(const XMLElementNotFoundException e)
//                 {
//                     std::cerr << e.what() << '\n';
//                 }
//             }
//         }
//         panelObject.setHasUi(false);
//     // }
//     return panelObject;
// }


