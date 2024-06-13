#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include "controller.h"
#include <string>

class GuiController : public Controller {
public:
    GuiController();
    ~GuiController();

    virtual void onPbGeneratePressed(std::string outDirectory) override final;
    virtual bool onPbWithUIPressed(std::string uiPath) override final;
    virtual bool onPbWithoutUIPressed(std::string name) override final;
    virtual bool onPbAssociatePressed(int button, int action) override final;
    virtual bool onPbDeassociatePressed(int button) override final;
    virtual void onPbSaveXmlPressed(std::string xmlPath) override final;
    virtual int onPbLoadXmlPressed(std::string xmlPath) override final;
    virtual void onPbAddButtonPressed(std::string name, std::string type, std::string action) override final;
    virtual int onPbDeletePanelPressed(std::string panel) override final;
    virtual void onPbDelButtonPressed(int button) override final;
    virtual void changeCurrentPanel(int index) override final;
    virtual bool onComboPanelsChanged(int index) override final;
    virtual void onHeaderSavePressed(SaesHeader* header) override final;
    virtual bool changeCurrentPanelSize(int h, int w) override final;
    virtual std::string panelInfo() override final;
};

#endif // GUICONTROLLER_H