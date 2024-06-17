#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <map>
#include <vector>


enum ButtonAction {
    APPLY, CANCEL, CHECK, RESET, CUSTOM1, CUSTOM2, NULLBUTTONACTION
};

static std::map<ButtonAction, std::string> ButtonActionToString = {
    {APPLY, "Apply"},
    {CANCEL, "Cancel"},
    {CHECK, "Check"},
    {RESET, "Reset"},
    {CUSTOM1, "Custom1"},
    {CUSTOM2, "Custom2"},
    {NULLBUTTONACTION, "null"}
};

/**
 * Clase que representa un botón del ui, con tres atributos y
 * sus getters y setters. Las acciones de boton tienen un
 * mapa que mapea cada enumerado con su etiqueta de texto.
*/
class Button {
private:
    std::string name;
    ButtonAction action;

public:
    Button() {};
    Button(std::string _name);
    Button(std::string _name, std::string _action);
    ~Button() {};

    std::string getName();
    ButtonAction getAction();

    void setName(std::string _name);
    void setAction(ButtonAction _action);
    void deleteAction();

    std::string toString();
};

#endif  