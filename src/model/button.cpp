#include "button.h"

Button::Button(std::string _name)
{
    name = _name;
    action = NULLBUTTONACTION;
}

Button::Button(std::string _name, std::string _action)
{
    name = _name;
    for (auto const& element : ButtonActionToString)
    {
        if (!element.second.compare(_action)) action = element.first;
    }
}

std::string Button::getName()
{
    return name;
}

ButtonAction Button::getAction()
{
    return action;
}

void Button::setName(std::string _name)
{
    name = _name;
}

void Button::setAction(ButtonAction _action)
{
    action = _action;
}

void Button::deleteAction() 
{
    action = NULLBUTTONACTION;
} 

std::string Button::toString()
{
    std::string str;
    str = "'" + name + "': action=" + ButtonActionToString.find(action)->second + "\n";
    return str;
}