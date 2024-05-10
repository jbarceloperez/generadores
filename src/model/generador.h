#ifndef GENERADOR_H
#define GENERADOR_H

#include "panel.h"
#include <map>

enum FileToGenerate 
{
    HEADER, GWHEADER, GW, QTCBHEADER, QTCB, UI, CMAKELISTS, FILES_END
};

enum TemplateMark
{
    NAME, NAME_CAPS, PANEL_APPLY_H, PANEL_APPLY_CPP, PANEL_CANCEL_H,
    PANEL_CANCEL_CPP, PANEL_CHECK_H, PANEL_CHECK_CPP, PANEL_RESET_H,
    PANEL_RESET_CPP, PANEL_CUSTOM1_H, PANEL_CUSTOM1_CPP, PANEL_CUSTOM2_H, 
    PANEL_CUSTOM2_CPP, ADD_FOOTER_BUTTON_APPLY, ADD_FOOTER_BUTTON_CANCEL, 
    ADD_FOOTER_BUTTON_CHECK, ADD_FOOTER_BUTTON_RESET, 
    ADD_FOOTER_BUTTON_CUSTOM1, ADD_FOOTER_BUTTON_CUSTOM2, GEOMETRY_W, 
    GEOMETRY_H, BUTTONS_UI, END_MARK
};


static std::map<TemplateMark, std::string> MarkStrings = {
    {NAME,                      "NAME"},
    {NAME_CAPS,                 "NAME_CAPS"},
    {PANEL_APPLY_H,             "PANEL_APPLY_H"},
    {PANEL_APPLY_CPP,           "PANEL_APPLY_CPP"},
    {PANEL_CANCEL_H,            "PANEL_CANCEL_H"},
    {PANEL_CANCEL_CPP,          "PANEL_CANCEL_CPP"},
    {PANEL_CHECK_H,             "PANEL_CHECK_H"},
    {PANEL_CHECK_CPP,           "PANEL_CHECK_CPP"},
    {PANEL_RESET_CPP,           "PANEL_RESET_CPP"},
    {PANEL_RESET_H,             "PANEL_RESET_H"},
    {PANEL_CUSTOM1_CPP,         "PANEL_CUSTOM1_CPP"},
    {PANEL_CUSTOM1_H,           "PANEL_CUSTOM1_H"},
    {PANEL_CUSTOM2_CPP,         "PANEL_CUSTOM2_CPP"},
    {PANEL_CUSTOM2_H,           "PANEL_CUSTOM2_H"},
    {ADD_FOOTER_BUTTON_APPLY,   "ADD_FOOTER_BUTTON_APPLY"},
    {ADD_FOOTER_BUTTON_CANCEL,  "ADD_FOOTER_BUTTON_CANCEL"},
    {ADD_FOOTER_BUTTON_CHECK,   "ADD_FOOTER_BUTTON_CHECK"},
    {ADD_FOOTER_BUTTON_CUSTOM1, "ADD_FOOTER_BUTTON_CUSTOM1"},
    {ADD_FOOTER_BUTTON_CUSTOM2, "ADD_FOOTER_BUTTON_CUSTOM2"},
    {ADD_FOOTER_BUTTON_RESET,   "ADD_FOOTER_BUTTON_RESET"},
    {GEOMETRY_W,                "GEOMETRY_W"},
    {GEOMETRY_H,                "GEOMETRY_H"},
    {BUTTONS_UI,                "BUTTONS_UI"}
};

void generatePanelFiles(GPanel p);

std::string writeFile(GPanel p, std::map<TemplateMark, std::string>& properties, FileToGenerate file);

std::string readTemplate(const std::string& filename);
void replaceMarks(std::string& code, const std::map<TemplateMark, std::string>& properties);
void fillPropertiesMap(GPanel p, std::map<TemplateMark, std::string> &properties);

void setButtonUi(std::map<TemplateMark, std::string> &props, GPanel &p, Button &b, std::string &str_buttons, TemplateMark mark1, TemplateMark mark2, TemplateMark mark3);

#endif // GENERATOR_H
