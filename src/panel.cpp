#include "Panel.h"

#define DEFAULT_X 50
#define DEFAULT_Y 50
#define DEFAULT_W 400
#define DEFAULT_H 300
#define DEFAULT_TYPE "simple"

// Constructor
Panel::Panel(std::string _name, int _x, int _y, int _w, int _h, std::string _type)
{
    name = _name;
    x = _x == -1 ? DEFAULT_X : _x;
    y = _y == -1 ? DEFAULT_Y : _y;
    w = _w == -1 ? DEFAULT_W : _w;
    h = _h == -1 ? DEFAULT_H : _h;
    type = _type;
    //std::cout << "\t\tPANEL CREADO\n";  // DEBUG
}

Panel::Panel(std::string _name)
{
    name = _name;
    x = DEFAULT_X;
    y = DEFAULT_Y;
    w = DEFAULT_W;
    h = DEFAULT_H;
    type = DEFAULT_TYPE;
}

// Destructor
Panel::~Panel()
{
    /*
    no es necesario liberar memoria de estructuras
    de la librería estandar, esto ya no es C
    */
}

// Getters
const std::string &Panel::getName() const
{
    return name;
}

int Panel::getX() const
{
    return x;
}

int Panel::getY() const
{
    return y;
}

int Panel::getWidth() const
{
    return w;
}

int Panel::getHeight() const
{
    return h;
}

std::string Panel::getType() const
{
    return type;
}

// Setters
void Panel::setX(int newX)
{
    x = newX;
}

void Panel::setY(int newY)
{
    y = newY;
}

void Panel::setWidth(int newWidth)
{
    w = newWidth;
}

void Panel::setHeight(int newHeight)
{
    h = newHeight;
}

void Panel::setType(std::string newTypeValue)
{
    type = newTypeValue;
}

std::string Panel::toString() const
{
    std::string str;
    str = "Class=panel.cpp\n";
    str += "{\n";
    str += "\tname=[" + name + "]\n";
    str += "\tcoords=[x=" + std::to_string(x) + ",y=" + std::to_string(y) + "]\n";
    str += "\tsize=[w=" + std::to_string(w) + ",h=" + std::to_string(h) + "]\n";
    str += "\ttype=" + type + "\n";
    str += "}\n";

    return str;
}