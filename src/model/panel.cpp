#include "panel.h"
#include "../controller.h"


// Constructor
GPanel::GPanel(std::string _name, int _w, int _h, PanelType _type)
{
    name = _name;
    w = _w == -1 ? DEFAULT_W : _w;
    h = _h == -1 ? DEFAULT_H : _h;
    type = _type;
    layout = DEFAULT_LAYOUT;
}

GPanel::GPanel(std::string _name)
{
    name = _name;
    w = DEFAULT_W;
    h = DEFAULT_H;
    type = PanelType::READ_ONLY;
    layout = DEFAULT_LAYOUT;
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

LayoutType GPanel::getLayout() const
{
    return layout;
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
            setType(pair.first);
            return;
        }
    }
    Controller::getInstance().printTrace(CRITICAL, "ERROR: PanelType '" + newTypeValue + "' does not exist.");
    // exception?
}

void GPanel::setLayout(std::string newLayout)
{
    for (const auto& pair : LayoutTypeToString)
    {
        if (!pair.second.compare(newLayout))
        {
            setLayout(pair.first);
            return;
        }
    }
    setLayout(DEFAULT_LAYOUT);
}

void GPanel::setLayout(LayoutType newLayout)
{
    layout = newLayout;
}

// Funcionalidad con los botones
void GPanel::addButton(ButtonType _type, std::string _name)
{
    Controller::getInstance().printTrace(TRACE, "Added button [" + _name + "]");
    buttons.push_back(Button(_name, _type));
    if (type == READ_ONLY) type = CONFIG;
    else if (type == EXTERNAL_UI_READ) type = EXTERNAL_UI_CONFIG;
}

void GPanel::addButton(std::string _name, std::string _type, std::string _action)
{
    Controller::getInstance().printTrace(TRACE, "Added button [" + _name + "]");
    buttons.push_back(Button(_name, _type, _action));
    if (type == READ_ONLY) type = CONFIG;
    else if (type == EXTERNAL_UI_READ) type = EXTERNAL_UI_CONFIG;
}

void GPanel::deleteButton(int button_index)
{
    buttons.erase(buttons.begin() + button_index);
    if (buttons.size() == 0)
    {
        if (type == CONFIG) type = READ_ONLY;
        else if (type == EXTERNAL_UI_CONFIG) type = EXTERNAL_UI_READ;
    }
}

void GPanel::addActionToButton(int button, ButtonAction action)
{
    buttons[button].setAction(action);
}

void GPanel::deleteActionToButton(int button)
{
    buttons[button].deleteAction();
}

std::string GPanel::toString() const
{
    std::string str;
    str = "PANEL [" + name + "]\n  ";
    str += "Size:[w=" + std::to_string(w) + ",h=" + std::to_string(h) + "]\n  ";
    str += "Type: " + PanelTypeToString.find(type)->second + "\n  ";
    str += "Layout: " + LayoutTypeToString.find(layout)->second + "\n  ";
    str += "Buttons:\n";
    for (Button b : buttons)
    {
        str += "   > " + b.toString();
    }

    return str;
}
