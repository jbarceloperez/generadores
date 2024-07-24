#ifndef GENERADOR_H
#define GENERADOR_H

#include "gpanel.h"
#include "../log/logger.h"
#include <map>
#include <string>

#define TEMPLATES_PATH "../templates/"
#define FULLPATH(x) (std::string(TEMPLATES_PATH) + x)

enum FileToGenerate 
{
    HEADER, GWHEADER, GW, QTCBHEADER, QTCB, UI, CMAKELISTS, DOXYFILE, TESTFILE, FILES_END
};

enum TemplateMark
{
    NAME, NAME_CAPS, PANEL_APPLY_H, PANEL_APPLY_CPP, PANEL_CANCEL_H,
    PANEL_CANCEL_CPP, PANEL_CHECK_H, PANEL_CHECK_CPP, PANEL_RESET_H,
    PANEL_RESET_CPP, PANEL_CUSTOM1_H, PANEL_CUSTOM1_CPP, PANEL_CUSTOM2_H, 
    PANEL_CUSTOM2_CPP, ADD_FOOTER_BUTTON_APPLY, ADD_FOOTER_BUTTON_CANCEL, 
    ADD_FOOTER_BUTTON_RESET, ADD_FOOTER_BUTTON_CUSTOM1, ADD_FOOTER_BUTTON_CUSTOM2, 
    GEOMETRY_W,  GEOMETRY_H, BUTTONS_UI, LAYOUT_UI, SAES_HEADER, UIXMLBUTTON,
    UIXMLBUTTON_WITHPOS, PANEL_OK_H, PANEL_OK_CPP, ADD_FOOTER_BUTTON_OK, 
    TESTS, TEST_FUNCTION, END_MARK
};

static std::map<FileToGenerate, std::string> FileTemplatePath = {
    {HEADER,        FULLPATH("Header.template")},
    {GWHEADER,      FULLPATH("GwHeader.template")},
    {GW,            FULLPATH("Gw.template")},
    {QTCBHEADER,    FULLPATH("QtCbHeader.template")},
    {QTCB,          FULLPATH("QtCb.template")},
    {UI,            FULLPATH("Ui.template")},
    {CMAKELISTS,    FULLPATH("CMakeLists.template")},
    {DOXYFILE,      FULLPATH("Doxyfile.template")},
    {TESTFILE,      FULLPATH("Testfile.template")}
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
    {PANEL_OK_CPP,              "PANEL_OK_CPP"},
    {PANEL_OK_H,                "PANEL_OK_H"},
    {ADD_FOOTER_BUTTON_OK,      "ADD_FOOTER_BUTTON_OK"},
    {ADD_FOOTER_BUTTON_APPLY,   "ADD_FOOTER_BUTTON_APPLY"},
    {ADD_FOOTER_BUTTON_CANCEL,  "ADD_FOOTER_BUTTON_CANCEL"},
    {ADD_FOOTER_BUTTON_CUSTOM1, "ADD_FOOTER_BUTTON_CUSTOM1"},
    {ADD_FOOTER_BUTTON_CUSTOM2, "ADD_FOOTER_BUTTON_CUSTOM2"},
    {ADD_FOOTER_BUTTON_RESET,   "ADD_FOOTER_BUTTON_RESET"},
    {GEOMETRY_W,                "GEOMETRY_W"},
    {GEOMETRY_H,                "GEOMETRY_H"},
    {BUTTONS_UI,                "BUTTONS_UI"},
    {LAYOUT_UI,                 "LAYOUT_UI"},
    {SAES_HEADER,               "SAES_HEADER"},
    {UIXMLBUTTON,               "UIXMLBUTTON"},
    {UIXMLBUTTON_WITHPOS,       "UIXMLBUTTON_WITHPOS"},
    {TESTS,                     "TESTS"},
    {TEST_FUNCTION,             "TEST_FUNCTION"}
};

class Generador {
private:
    Logger* log;

public:
Generador();

void generatePanelFiles(GPanel p, std::string outDirectory);

void writeFile(const std::string& path, std::map<std::string, std::string> &documentation, std::map<TemplateMark, std::string> &properties, FileToGenerate file);
std::string readTemplate(const std::string &filename);
void replaceMarks(std::string &code, const std::map<TemplateMark, std::string> &properties);

std::map<TemplateMark, std::string> fillPropertiesMap(GPanel p);
void fillTests(GPanel &p, std::map<TemplateMark, std::string> &code_chunks, std::map<TemplateMark, std::string> &props);
void fillButtonMarks(GPanel &p, std::map<TemplateMark, std::string> &props, std::map<TemplateMark, std::string> &code_chunks);
void setButtonData(std::map<TemplateMark, std::string> &props, std::map<TemplateMark, std::string> &code_chunks, GPanel &p, GButton &b, std::string &str_buttons, TemplateMark mark1, TemplateMark mark2, TemplateMark mark3);

std::map<TemplateMark, std::string> readCodeChunks(const std::string &filename);
std::map<std::string, std::string> readDocumentation(const std::string &filename);
void processChunkLine(std::string &line, bool &inChunk, std::string &currentChunk, std::map<TemplateMark, std::string> &codeChunks, std::ostringstream &currentCode);
void processDocLine(std::string &line, bool &inChunk, std::string &currentChunk, std::map<std::string, std::string> &documentation, std::ostringstream &currentDoc);
void addDocumentation(std::string &code, const std::map<std::string, std::string> &documentation, std::string name);

};


#endif // GENERATOR_H
