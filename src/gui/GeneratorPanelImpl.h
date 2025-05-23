#ifndef GENERATORPANELIMPL_H
#define GENERATORPANELIMPL_H

#pragma once

#include <QFrame>
#include <memory>
#include "HeaderConfigPanel.h"
#include "../controller/guicontroller.h"


class GeneratorPanelImpl : public QFrame
{
    Q_OBJECT

public:
    GeneratorPanelImpl();
    ~GeneratorPanelImpl();

private slots:
    void handleButtonClicked();
    void handleSelectedPanel();
    void handleLayoutCombobox();
    void handleSpinBoxWidth();
    void handleSpinBoxHeight();
    void handleTestsCheckbox();

private:
    class PrivateData;
    std::unique_ptr<PrivateData> p_impl;

    void onPbWithUIPressed();
    void onPbWithoutUIPressed();
    void onPbGeberatePressed();
    void onPbAssociatePressed();
    void onPbDeassociatePressed();
    void onPbFilePressed();
    void onPbSaveXmlPressed();
    void onPbAddButtonPressed();
    void onPbDelButtonPressed();
    void onPbLoadXmlPressed();
    void onPbDeletePanelPressed();

    void updateHmi();
    void updateButtons();
    void updatePanelSettings();
    void updateTxtAssociate();

    std::unique_ptr<HeaderConfigPanelImpl> headerPanel;
    GuiController* controller;
    Logger* log;
};

#endif // GENERATORPANEL_H
