#include <string>
#include <map>
#ifndef PANEL_H
#define PANEL_H

enum PanelType {
    READ_ONLY, CONFIG, EXTERNAL_UI, PANELS_END
};

std::map<PanelType, std::string> PanelTypeStrings = {
    {READ_ONLY, "readonly"},
    {CONFIG, "config"},
    {EXTERNAL_UI, "ui"},
    {PANELS_END, ""}
};

class Panel {
private:
    std::string name;   // Nombre del panel
    int x, y;           // Coordenadas del panel en la pantalla
    int w, h;           // Ancho y altura del panel en píxeles
    PanelType type;     // Propiedad
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

    // Setters
    void setX(int newX);
    void setY(int newY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setType(PanelType newTypeValue);
    void setType(std::string newTypeValue);
    void setHasUi(bool newValue);

    std::string toString() const;
};

#endif // PANEL_H
