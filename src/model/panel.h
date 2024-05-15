#ifndef PANEL_H
#define PANEL_H

#include <string>
#include <map>
#include <vector>

#include "button.h"

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
    std::string uipath;             // Ruta al archivo ui, si lo tuvise
    std::vector<Button> buttons;    // Collección de botones

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
    std::vector<Button> getButtons() const;

    // Setters
    void setName(std::string _name);
    void setUiPath(std::string _ui);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setType(PanelType newTypeValue);
    void setType(std::string newTypeValue);
    
    // Funcionalidad con los botones
    void addButton(ButtonType type, std::string name);
    void addButton(std::string name, std::string type, std::string action);
    void deleteButton(int button);
    void addActionToButton(int button, ButtonAction action);
    void deleteActionToButton(int button);

    std::string toString() const;
};

#endif // PANEL_H
