#include "button.h"

Button::Button(std::string _name, ButtonType _type)
{
    name = _name;
    type = _type;
    action = NULLBUTTONACTION;
}

Button::Button(std::string _name, std::string _type, std::string _action)
{
    name = _name;
    for (auto const& element : ButtonTypeToString)
    {
        if (!element.second.compare(_type)) type = element.first;
    }
    for (auto const& element : ButtonActionToString)
    {
        if (!element.second.compare(_action)) action = element.first;
    }
}

std::string Button::getName()
{
    return name;
}

ButtonType Button::getType()
{
    return type;
}

ButtonAction Button::getAction()
{
    return action;
}

void Button::setName(std::string _name)
{
    name = _name;
}

void Button::setType(ButtonType _type)
{
    type = _type;
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
    str = "'" + name + "': " + ButtonTypeToString.find(type)->second;
    str+=", action=" + ButtonActionToString.find(action)->second + "\n";
    return str;
}