#include <map>

static std::map<TemplateMark, std::string> Functions = {
    {PANEL_APPLY_H,             "/** @brief Método con la funcionalidad del botón \"Apply\". */\n\tvirtual void panelApply()override final;"},
    {PANEL_APPLY_CPP,           "//----------------------------------------------------------------\nvoid %sQtCb::panelApply()\n{\n    // Implementation here\n}"},
    {PANEL_CANCEL_H,            "/** @brief Método con la funcionalidad del botón \"Cancel\". */\n\tvirtual void panelCancel()override final;"},
    {PANEL_CANCEL_CPP,          "//----------------------------------------------------------------\nvoid %sQtCb::panelCancel()\n{\n    // Implementation here\n}"},
    {PANEL_CHECK_H,             "/** @brief Método con la funcionalidad del botón \"Check\". */\n\tvirtual bool panelCheck()override final;"},
    {PANEL_CHECK_CPP,           "//----------------------------------------------------------------\nbool %sQtCb::panelCheck()\n{\n    // Implementation here\n}"},
    {PANEL_RESET_CPP,           "//----------------------------------------------------------------\nvoid %sQtCb::panelReset()\n{\n    // Implementation here\n}"},
    {PANEL_RESET_H,             "/** @brief Método con la funcionalidad del botón \"Reset\". */\n\tvirtual void panelReset()override final;"},
    {PANEL_CUSTOM1_CPP,         "//----------------------------------------------------------------\nvoid %sQtCb::panelCustom1()\n{\n   // Implementation here\n}"},
    {PANEL_CUSTOM1_H,           "/** @brief Método con la funcionalidad del botón \"Custom1\". */\n\tvirtual void panelCustom1()override final;"},
    {PANEL_CUSTOM2_CPP,         "//----------------------------------------------------------------\nvoid %sQtCb::panelCustom2()\n{\n   // Implementation here\n}"},
    {PANEL_CUSTOM2_H,           "/** @brief Método con la funcionalidad del botón \"Custom2\". */\n\tvirtual void panelCustom2()override final;"},
    {ADD_FOOTER_BUTTON_APPLY,   "addFooterButton(Footer::Button_Apply, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CANCEL,  "addFooterButton(Footer::Button_Cancel, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CHECK,   "addFooterButton(Footer::Button_Check, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CUSTOM1, "addFooterButton(Footer::Button_Custom_1, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CUSTOM2, "addFooterButton(Footer::Button_Custom_2, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_RESET,   "addFooterButton(Footer::Button_Reset, p_impl->ui.%s);"}
};

enum CodeSnippet
{
    UIXMLBUTTON, UIXMLBUTTON_WITHPOS 
};

static std::map<CodeSnippet, std::string> CodeSnippets = {
    {UIXMLBUTTON,           "\t<item>\n\t    <widget class=\"%s\" name=\"%s\">\n\t     <property name=\"text\">\n\t      <string>%s</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"},
    {UIXMLBUTTON_WITHPOS,   "\t<item row=\"%d\" column=\"%d\">\n\t    <widget class=\"%s\" name=\"%s\">\n\t     <property name=\"text\">\n\t      <string>%s</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"}   
};
