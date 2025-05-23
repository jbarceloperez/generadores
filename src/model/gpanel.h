#ifndef PANEL_H
#define PANEL_H

#include <string>
#include <map>
#include <vector>
#include "gbutton.h"
#include "saesheader.h"
#include "../log/logger.h"

#define DEFAULT_W 400
#define DEFAULT_H 300
#define DEFAULT_LAYOUT QHBOXLAYOUT

enum LayoutType {
    QHBOXLAYOUT, QVBOXLAYOUT, QGRIDLAYOUT, QFORMLAYOUT, EXTERNAL_UI
};

static std::map<LayoutType, std::string> LayoutTypeToString = {
    {QGRIDLAYOUT, "QGridLayout"},
    {QHBOXLAYOUT, "QHBoxLayout"},
    {QVBOXLAYOUT, "QVBoxLayout"},
    {QFORMLAYOUT, "QFormLayout"},
    {EXTERNAL_UI, "<EXTERNAL UI>"}
};

enum PanelType {
    READ_ONLY, CONFIG, EXTERNAL_UI_READ, EXTERNAL_UI_CONFIG, PanelType_END
};

static std::map<PanelType, std::string> PanelTypeToString = {
    {READ_ONLY, "readonly"},
    {CONFIG, "config"},
    {EXTERNAL_UI_READ, "ui_readonly"},
    {EXTERNAL_UI_CONFIG, "ui_config"},
    {PanelType_END, ""}
};

/**
 * Clase que representa un panel. El atributo clave es el nombre,
 * y contiene distintas propiedades además de una colección de botones.
*/
class GPanel {
private:
    std::string name;               // Nombre del panel
    int w, h;                       // Ancho y altura del panel en píxeles
    PanelType type;                 // Propiedad
    LayoutType layout;              // Tipo de layout del panel
    std::string uipath;             // Ruta al archivo ui, si lo tuvise
    std::vector<GButton> buttons;   // Collección de botones
    SaesHeader header;              // Cabecera SAES del panel
    bool test = true;               // Indica si debe generar tests
    Logger* log;                    // Logger

public:
    // Constructor
    GPanel(std::string name, int width, int height, PanelType type);
    GPanel(std::string name);
    GPanel() {};
    ~GPanel() {};

    // Getters
    const std::string& getName() const;
    const std::string& getUiPath() const;
    int getWidth() const;
    int getHeight() const;
    PanelType getType() const;
    LayoutType getLayout() const;
    std::vector<GButton> getButtons() const;
    SaesHeader getHeader() const;
    bool getTest() const;

    // Setters
    void setName(std::string _name);
    void setUiPath(std::string _ui);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setType(PanelType newTypeValue);
    void setType(std::string newTypeValue);
    void setLayout(std::string newLayout);
    void setLayout(LayoutType newLayout);
    void setTest(bool newValue);

    // Funcionalidad con los botones
    void addButton(std::string name);
    void addButton(std::string name, std::string action);
    void deleteButton(int button);
    void addActionToButton(int button, ButtonAction action);
    void deleteActionToButton(int button);

    // Funcionalidad con la cabecera
    void setHeaderElement(HeaderElement element, std::string value);
    std::string getHeaderElement(HeaderElement element);
    std::string getHeaderString();

    std::string toString() const;
};

#endif // PANEL_H
