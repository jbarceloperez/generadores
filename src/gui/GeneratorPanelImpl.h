#ifndef GENERATORPANELIMPL_H
#define GENERATORPANELIMPL_H

#pragma once

#include <QFrame>
#include <memory>


class GeneratorPanelImpl : public QFrame
{
    Q_OBJECT

public:
    GeneratorPanelImpl();
    ~GeneratorPanelImpl();    

private slots:
    void handleButtonClicked();
    void handleSelectedPanel();

private:
    class PrivateData;
    std::unique_ptr<PrivateData> p_impl;
    void onPbWithUIPressed();
    void updatePanels();
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
    void updateTxtAssociate();
};

#endif // GENERATORPANEL_H
