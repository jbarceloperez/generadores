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

class Panel {
private:
    std::string name;   // Nombre del panel
    int x, y;           // Coordenadas del panel en la pantalla
    int w, h;           // Ancho y altura del panel en píxeles
    PanelType type;     // Propiedad
    std::vector<Button> buttons;
    bool ui;            // true si tiene ya ui, false si no 
                        // TODO: el bool ui ¿es info redundante?

public:
    // Constructor
    Panel(std::string name, int posX, int posY, int width, int height, PanelType type);
    Panel(std::string name);
    Panel();

    // Destructor
    ~Panel();

    // Getters
    const std::string& getName() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    PanelType getType() const;
    bool hasUi() const;
    std::vector<Button> getButtons() const;

    // Setters
    void setName(std::string _name);
    void setX(int newX);
    void setY(int newY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setType(PanelType newTypeValue);
    void setType(std::string newTypeValue);
    void setHasUi(bool newValue);
    
    void addButton(ButtonType type, std::string name);


    std::string toString() const;
};

#endif // PANEL_H
