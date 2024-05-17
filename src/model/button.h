#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <map>
#include <vector>


enum ButtonType {
    QPUSHBUTTON, QRADIOBUTTON, QCHECKBOX
};

enum ButtonAction {
    APPLY, CANCEL, CHECK, RESET, CUSTOM1, CUSTOM2, NULLBUTTONACTION
};

static std::map<ButtonType, std::string> ButtonTypeToString = {
    {QPUSHBUTTON, "QPushButton"},
    {QRADIOBUTTON, "QRadioButton"},
    {QCHECKBOX, "QCheckBox"}
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
 * sus getters y setters. Los tipos de botón y acción tienen un
 * mapa que mapea cada enumerado con su etiqueta de texto.
*/
class Button {
private:
    std::string name;
    ButtonType type;
    ButtonAction action;

public:
    Button() {};
    Button(std::string _name, ButtonType _type);
    Button(std::string _name, std::string _type, std::string _action);
    ~Button() {};

    std::string getName() {return name;}
    ButtonType getType() {return type;}
    ButtonAction getAction() {return action;}

    void setName(std::string _name) {name = _name;}
    void setType(ButtonType _type) {type = _type;}
    void setAction(ButtonAction _action) {action = _action;}
    void deleteAction() {action = NULLBUTTONACTION;} 

    std::string toString();
};

#endif  