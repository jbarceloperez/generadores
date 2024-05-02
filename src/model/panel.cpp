#include "panel.h"
#include "../controller.h"

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

// Getters
const std::string &GPanel::getName() const
{
    return name;
}

const std::string &GPanel::getUiPath() const
{
    return uipath;
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

// Setters
void GPanel::setName(std::string _name)
{
    name = _name;
}
void GPanel::setUiPath(std::string _uipath)
{
    uipath = _uipath;
}

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
    for (const auto& pair : PanelTypeToString)
    {
        if (!pair.second.compare(newTypeValue))
        {
            type = pair.first;
            return;
        }
    }
    Controller::getInstance().printTrace(CRITICAL, "ERROR: PanelType '" + newTypeValue + "' does not exist.");
    // exception?
}

// Funcionalidad con los botones
void GPanel::addButton(ButtonType type, std::string name)
{
    Controller::getInstance().printTrace(TRACE, "Added button [" + name + "]");
    buttons.push_back(Button(name, type));
}

void GPanel::addButton(std::string _name, std::string _type, std::string _action)
{
    Controller::getInstance().printTrace(TRACE, "Added button [" + name + "]");
    buttons.push_back(Button(_name, _type, _action));
}

void GPanel::addActionToButton(int button, ButtonAction action)
{
    buttons[button].setAction(action);
}



std::string GPanel::toString() const
{
    std::string str;
    str = "Class=GPanel\n";
    str += "{\n";
    str += " name=[" + name + "]\n";
    str += " size=[w=" + std::to_string(w) + ",h=" + std::to_string(h) + "]\n";
    str += " type=" + PanelTypeToString.find(type)->second + "\n";
    str += " buttons={\n";
    for (Button b : buttons)
    {
        str += "  " + b.toString();
    }
    str += "}\n";

    return str;
}
