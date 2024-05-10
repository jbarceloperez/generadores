#ifndef PANEL_H
#define PANEL_H

#include <string>
#include <map>
#include <vector>

enum PanelType {
    READ_ONLY, CONFIG, EXTERNAL_UI_READ, EXTERNAL_UI_CONFIG, PanelType_END
};

enum ButtonType {
    QPUSHBUTTON, QRADIOBUTTON, QCHECKBOX
};

enum ButtonAction {
    APPLY, CANCEL, CHECK, RESET, CUSTOM1, CUSTOM2, NULLBUTTONACTION
};

static std::map<PanelType, std::string> PanelTypeToString = {
    {READ_ONLY, "readonly"},
    {CONFIG, "config"},
    {EXTERNAL_UI_READ, "ui_readonly"},
    {EXTERNAL_UI_CONFIG, "ui_config"},
    {PanelType_END, ""}
};

static std::map<ButtonType, std::string> ButtonTypeToString = {
    {QPUSHBUTTON, "QPushButton"},
    {QRADIOBUTTON, "QRadioButton"},
    {QCHECKBOX, "QCheckBox"}
};

static std::map<ButtonAction, std::string> ButtonActionToString = {
    {APPLY, "Apply"},
    {CANCEL, "Cancel"},
    {CHECK, "Check"},
    {RESET, "Reset"},
    {CUSTOM1, "Custom1"},
    {CUSTOM2, "Custom2"},
    {NULLBUTTONACTION, "null"}
};
/**
 * Clase que representa un botón del ui, con tres atributos y
 * sus getters y setters. Los tipos de botón y acción tienen un
 * mapa que mapea cada enumerado con su etiqueta de texto.
*/
class Button {
private:
    std::string name;
    ButtonType type;
    ButtonAction action;

public:
    Button() {};
    Button(std::string _name, ButtonType _type) {
        name = _name;
        type = _type;
        action = NULLBUTTONACTION;
    };
    Button(std::string _name, std::string _type, std::string _action) {
        name = _name;
        for (auto const& element : ButtonTypeToString)
        {
            if (!element.second.compare(_type)) type = element.first;
        }
        for (auto const& element : ButtonActionToString)
        {
            if (!element.second.compare(_action)) action = element.first;
        }
    };
    ~Button() {};

    std::string getName() {return name;}
    ButtonType getType() {return type;}
    ButtonAction getAction() {return action;}

    void setName(std::string _name) {name = _name;}
    void setType(ButtonType _type) {type = _type;}
    void setAction(ButtonAction _action) {action = _action;}
    void deleteAction() {action = NULLBUTTONACTION;} 

    std::string toString() {
        std::string str;
        str = "'" + name + "': " + ButtonTypeToString.find(type)->second;
        str+=", action=" + ButtonActionToString.find(action)->second + "\n";
        return str;
    }
};

/**
 * 
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
