#include "gbutton.h"

GButton::GButton(std::string _name)
{
    name = _name;
    action = NULLBUTTONACTION;
}

GButton::GButton(std::string _name, std::string _action)
{
    name = _name;
    for (auto const& element : ButtonActionToString)
    {
        if (!element.second.compare(_action)) action = element.first;
    }
}

std::string GButton::getName()
{
    return name;
}

ButtonAction GButton::getAction()
{
    return action;
}

void GButton::setName(std::string _name)
{
    name = _name;
}

void GButton::setAction(ButtonAction _action)
{
    action = _action;
}

void GButton::deleteAction() 
{
    action = NULLBUTTONACTION;
} 

std::string GButton::toString()
{
    std::string str;
    str = "'" + name + "': action=" + ButtonActionToString.find(action)->second + "\n";
    return str;
}