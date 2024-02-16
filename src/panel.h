#include <string>
#ifndef PANEL_H
#define PANEL_H

class Panel {
private:
    std::string name; // Nombre del panel
    int x, y; // Coordenadas del panel en la pantalla
    int w, h; // Ancho y altura del panel en píxeles
    bool fixed; // Propiedad que indica si el tamaño del panel es fijo o no

public:
    // Constructor
    Panel(std::string name, int posX, int posY, int width, int height, bool fixed);
    Panel(std::string name);

    // Destructor
    ~Panel();

    // Getters
    const std::string& getName() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    bool isFixed() const;

    // Setters
    void setX(int newX);
    void setY(int newY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setFixed(bool newFixedValue);

    std::string toString() const;
};

#endif // PANEL_H
