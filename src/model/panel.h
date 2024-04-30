#ifndef PANEL_H
#define PANEL_H

#include <string>
#include <map>
#include <vector>

enum PanelType {
    READ_ONLY, CONFIG, EXTERNAL_UI_READ, EXTERNAL_UI_CONFIG, PANELS_END
};

enum ButtonType {
    QPUSHBUTTON, QRADIOBUTTON, QCHECKBOX
};

enum ButtonAction {
    APPLY, CANCEL, CHECK, RESET, CUSTOM1, CUSTOM2
};

static std::map<PanelType, std::string> PanelTypeToStrings = {
    {READ_ONLY, "readonly"},
    {CONFIG, "config"},
    {EXTERNAL_UI_READ, "ui_readonly"},
    {EXTERNAL_UI_CONFIG, "ui_config"},
    {PANELS_END, ""}
};

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
    };
    ~Button() {};

    std::string getName() {return name;}
    ButtonType getType() {return type;}
    ButtonAction getAction() {return action;}

    void setName(std::string _name) {name = _name;}
    void setType(ButtonType _type) {type = _type;}
    void setAction(ButtonAction _action) {action = _action;}

    std::string toString() {
        std::string str;
        str = "'" + name + "': type=";
        if (type==QRADIOBUTTON) str+="QRadioButton, action=";
        else if(type==QPUSHBUTTON) str+="QPushButton, action=";
        else str+="QCheckButton, action=";
        switch (action)
        {
        case APPLY:
            str+="panelApply\n";
            break;
        case CANCEL:
            str+="panelCancel\n";
            break;
        case CHECK:
            str+="panelCheck\n";
            break;
        case RESET:
            str+="panelReset\n";
            break;
        case CUSTOM1:
            str+="panelCustom1\n";
            break;
        case CUSTOM2:
            str+="panelCustom2\n";
            break;
        default:
            str+="null\n";
            break;
        }
        return str;
    }
};

class GPanel {
private:
    std::string name;   // Nombre del panel
    int w, h;           // Ancho y altura del panel en píxeles
    PanelType type;     // Propiedad
    std::vector<Button> buttons;

public:
    // Constructor
    GPanel(std::string name, int width, int height, PanelType type);
    GPanel(std::string name);
    GPanel();

    // Destructor
    ~GPanel();

    // Getters
    const std::string& getName() const;
    int getWidth() const;
    int getHeight() const;
    PanelType getType() const;
    std::vector<Button> getButtons() const;

    // Setters
    void setName(std::string _name);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setType(PanelType newTypeValue);
    void setType(std::string newTypeValue);
    
    void addButton(ButtonType type, std::string name);
    void addActionToButton(int button, ButtonAction action);


    std::string toString() const;
};

#endif // PANEL_H
