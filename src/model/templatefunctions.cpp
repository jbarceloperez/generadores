#include <map>
#include "generador.h"
#include "panel.h"

static std::map<TemplateMark, std::string> Functions = {
    {PANEL_APPLY_H,             "virtual void panelApply()override final;"},
    {PANEL_APPLY_CPP,           "//----------------------------------------------------------------\nvoid %sQtCb::panelApply()\n{\n    reset()\n}"},
    {PANEL_CANCEL_H,            "virtual void panelCancel()override final;"},
    {PANEL_CANCEL_CPP,          "//----------------------------------------------------------------\nvoid %sQtCb::panelCancel()\n{\n    reset()\n}"},
    {PANEL_CHECK_H,             "virtual bool panelCheck()override final;"},
    {PANEL_CHECK_CPP,           "//----------------------------------------------------------------\nbool %sQtCb::panelCheck()\n{\n    return true;\n}"},
    {PANEL_RESET_CPP,           "//----------------------------------------------------------------\nvoid %sQtCb::panelReset()\n{\n    reset()\n}"},
    {PANEL_RESET_H,             "virtual void panelReset()override final;"},
    {PANEL_CUSTOM1_CPP,         "//----------------------------------------------------------------\nvoid %sQtCb::panelCustom1()\n{\n\n}"},
    {PANEL_CUSTOM1_H,           "virtual void panelCustom1();"},
    {PANEL_CUSTOM2_CPP,         "//----------------------------------------------------------------\nvoid %sQtCb::panelCustom2()\n{\n\n}"},
    {PANEL_CUSTOM2_H,           "virtual void panelCustom2();"},
    {ADD_FOOTER_BUTTON_APPLY,   "addFooterButton(Footer::Button_Apply, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CANCEL,  "addFooterButton(Footer::Button_Cancel, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CHECK,   "addFooterButton(Footer::Button_Check, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CUSTOM1, "addFooterButton(Footer::Button_Custom1, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_CUSTOM2, "addFooterButton(Footer::Button_Custom2, p_impl->ui.%s);"},
    {ADD_FOOTER_BUTTON_RESET,   "addFooterButton(Footer::Button_Reset, p_impl->ui.%s);"}
};

static std::map<ButtonAction, std::string> Buttons_XML = {
    {ButtonAction::APPLY,       "\t<item>\n\t    <widget class=\"QPushButton\" name=\"pbApply\">\n\t     <property name=\"text\">\n\t      <string>Apply</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"},
    {ButtonAction::CANCEL,      "\t<item>\n\t    <widget class=\"QPushButton\" name=\"pbCancel\">\n\t     <property name=\"text\">\n\t      <string>Cancel</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"},
    {ButtonAction::CHECK,       "\t<item>\n\t    <widget class=\"QPushButton\" name=\"pbCheck\">\n\t     <property name=\"text\">\n\t      <string>Check</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"},
    {ButtonAction::RESET,       "\t<item>\n\t    <widget class=\"QPushButton\" name=\"pbReset\">\n\t     <property name=\"text\">\n\t      <string>Reset</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"},
    {ButtonAction::CUSTOM1,     "\t<item>\n\t    <widget class=\"%s\" name=\"%s\">\n\t     <property name=\"text\">\n\t      <string>%s</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"},
    {ButtonAction::CUSTOM2,     "\t<item>\n\t    <widget class=\"%s\" name=\"%s\">\n\t     <property name=\"text\">\n\t      <string>%s</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"},
    {ButtonAction::NULLBUTTONACTION,     "\t<item>\n\t    <widget class=\"%s\" name=\"%s\">\n\t     <property name=\"text\">\n\t      <string>%s</string>\n\t     </property>\n\t     </widget>\n\t   </item>\n"}    
};
