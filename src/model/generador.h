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
    PANEL_RESET_CPP, PANEL_CUSTOM_H, PANEL_CUSTOM_CPP, ADD_FOOTER_BUTTON_APPLY,
    ADD_FOOTER_BUTTON_CANCEL, ADD_FOOTER_BUTTON_CHECK, ADD_FOOTER_BUTTON_RESET,
    END_MARK
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
    {PANEL_CUSTOM_CPP,          "PANEL_CUSTOM_CPP"},
    {PANEL_CUSTOM_H,            "PANEL_CUSTOM_H"},
    {PANEL_CUSTOM_CPP,          "PANEL_CUSTOM_CPP"},
    {ADD_FOOTER_BUTTON_APPLY,   "ADD_FOOTER_BUTTON_APPLY"},
    {ADD_FOOTER_BUTTON_CANCEL,  "ADD_FOOTER_BUTTON_CANCEL"},
    {ADD_FOOTER_BUTTON_CHECK,   "ADD_FOOTER_BUTTON_CHECK"},
    {ADD_FOOTER_BUTTON_RESET,   "ADD_FOOTER_BUTTON_RESET"}

};

void generateFiles(Panel p);
void generateFilesWithUi(Panel p);

std::string writeFile(Panel p, std::map<TemplateMark, std::string>& properties, FileToGenerate file);

std::string readTemplate(const std::string& filename);
void replaceMarks(std::string& code, const std::map<TemplateMark, std::string>& properties);
void fillPropertiesMap(Panel p, std::map<TemplateMark, std::string>& properties);


#endif  // GENERATOR_H
