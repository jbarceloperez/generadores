#ifndef GENERADOR_H
#define GENERADOR_H

#include "gpanel.h"
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
    GEOMETRY_H, BUTTONS_UI, LAYOUT_UI, SAES_HEADER, UIXMLBUTTON,
    UIXMLBUTTON_WITHPOS, END_MARK
};

static std::map<FileToGenerate, std::string> FileTemplatePath = {
    {HEADER,        "../templates/Header.template"},
    {GWHEADER,      "../templates/GwHeader.template"},
    {GW,            "../templates/Gw.template"},
    {QTCBHEADER,    "../templates/QtCbHeader.template"},
    {QTCB,          "../templates/QtCb.template"},
    {UI,            "../templates/Ui.template"},
    {CMAKELISTS,    "../templates/CMakeLists.template"}
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
    {BUTTONS_UI,                "BUTTONS_UI"},
    {LAYOUT_UI,                 "LAYOUT_UI"},
    {SAES_HEADER,               "SAES_HEADER"},
    {UIXMLBUTTON,               "UIXMLBUTTON"},
    {UIXMLBUTTON_WITHPOS,       "UIXMLBUTTON_WITHPOS"}
};

void generatePanelFiles(GPanel p);

void writeFile(const std::string& path, const std::string& srcDirPath, GPanel &p, std::map<TemplateMark, std::string> &properties, FileToGenerate file);
std::string readTemplate(const std::string &filename);
void replaceMarks(std::string &code, const std::map<TemplateMark, std::string> &properties);

void fillPropertiesMap(GPanel p, std::map<TemplateMark, std::string> &properties);
void fillButtonMarks(GPanel &p, std::map<TemplateMark, std::string> &props, std::map<TemplateMark, std::string> &code_chunks);
void setButtonData(std::map<TemplateMark, std::string> &props, std::map<TemplateMark, std::string> &code_chunks, GPanel &p, Button &b, std::string &str_buttons, TemplateMark mark1, TemplateMark mark2, TemplateMark mark3);

std::map<TemplateMark, std::string> readCodeChunks(const std::string &filename);
void processLine(std::string &line, bool &inChunk, std::string &currentChunk, std::map<TemplateMark, std::string> &codeChunks, std::ostringstream &currentCode);

#endif // GENERATOR_H
