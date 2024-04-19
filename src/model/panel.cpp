#include "Panel.h"
#include <iostream>     // para los cout, no debe quedarse cuando haya logger funcional

#define DEFAULT_X 50
#define DEFAULT_Y 50
#define DEFAULT_W 400
#define DEFAULT_H 300


// Constructor
Panel::Panel(std::string _name, int _x, int _y, int _w, int _h, PanelType _type)
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
    type = PanelType::READ_ONLY;
}

Panel::Panel(){}

// Destructor
Panel::~Panel() {}

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

PanelType Panel::getType() const
{
    return type;
}

bool Panel::hasUi() const
{   
    return ui;
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

void Panel::setType(PanelType newTypeValue)
{
    type = newTypeValue;
}

void Panel::setType(std::string newTypeValue)
{
    for (const auto& pair : PanelTypeStrings)
    {
        if (!pair.second.compare(newTypeValue))
        {
            type = pair.first;
            return;
        }
    }
    // TODO: logear esto correctamente
    std::cerr << "ERROR: PanelType '" << newTypeValue << "' does not exist\n";
    // exception?
}

void Panel::setHasUi(bool newValue)
{
    ui = newValue;
}

std::string Panel::toString() const
{
    std::string str;
    str = "Class=panel.cpp\n";
    str += "{\n";
    str += "\tname=[" + name + "]\n";
    str += "\tcoords=[x=" + std::to_string(x) + ",y=" + std::to_string(y) + "]\n";
    str += "\tsize=[w=" + std::to_string(w) + ",h=" + std::to_string(h) + "]\n";
    str += "\ttype=" + PanelTypeStrings.find(type)->second + "\n";
    str += "}\n";

    return str;
}