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

static std::map<PanelType, std::string> PanelTypeToStrings = {
    {READ_ONLY, "readonly"},
    {CONFIG, "config"},
    {EXTERNAL_UI_READ, "ui_r"},
    {EXTERNAL_UI_CONFIG, "ui_c"},
    {PANELS_END, ""}
};

class Button {
private:
    std::string name;
    ButtonType type;
public:
    Button() {};
    Button(std::string _name, ButtonType _type) {
        name = _name;
        type = _type;
    };
    ~Button() {};

    std::string getName() {return name;};
    ButtonType getType() {return type;};

    void setName(std::string _name) {name = _name;}
    void setName(ButtonType _type) {type = _type;}
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


    std::string toString() const;
};

#endif // PANEL_H
