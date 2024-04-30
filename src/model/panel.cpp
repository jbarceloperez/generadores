#include "panel.h"
#include "../controller.h"
#include <iostream>     // para los cout, no debe quedarse cuando haya logger funcional

#define DEFAULT_W 400
#define DEFAULT_H 300


// Constructor
GPanel::GPanel(std::string _name, int _w, int _h, PanelType _type)
{
    name = _name;
    w = _w == -1 ? DEFAULT_W : _w;
    h = _h == -1 ? DEFAULT_H : _h;
    type = _type;
}

GPanel::GPanel(std::string _name)
{
    name = _name;
    w = DEFAULT_W;
    h = DEFAULT_H;
    type = PanelType::READ_ONLY;
}

GPanel::GPanel(){}

// Destructor
GPanel::~GPanel() {}

// Getters
const std::string &GPanel::getName() const
{
    return name;
}


int GPanel::getWidth() const
{
    return w;
}

int GPanel::getHeight() const
{
    return h;
}

PanelType GPanel::getType() const
{
    return type;
}

std::vector<Button> GPanel::getButtons() const
{
    return buttons;
}

void GPanel::setName(std::string _name)
{
    name = _name;
}

// Setters
void GPanel::setWidth(int newWidth)
{
    w = newWidth;
}

void GPanel::setHeight(int newHeight)
{
    h = newHeight;
}

void GPanel::setType(PanelType newTypeValue)
{
    type = newTypeValue;
}

void GPanel::setType(std::string newTypeValue)
{
    for (const auto& pair : PanelTypeToStrings)
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


void GPanel::addButton(ButtonType type, std::string name)
{
    Controller::getInstance().printTrace(TRACE, "Added button [" + name + "]");
    buttons.push_back(Button(name, type));
}

std::string GPanel::toString() const
{
    std::string str;
    str = "Class=GPanel\n";
    str += "{\n";
    str += " name=[" + name + "]\n";
    str += " size=[w=" + std::to_string(w) + ",h=" + std::to_string(h) + "]\n";
    str += " type=" + PanelTypeToStrings.find(type)->second + "\n";
    str += "}\n";

    return str;
}
