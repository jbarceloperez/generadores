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
    void updateTxtAssociate();
    

private slots:
    void handleButtonClicked();
    void handleSelectedPanel();

private:
    class PrivateData;
    std::unique_ptr<PrivateData> p_impl;
    void onPbWithUIPressed();
    void updateButtons();
    void onPbWithoutUIPressed();
    void onPbGeberatePressed();
    void onPbAssociatePressed();
    void onPbDeassociatePressed();
    void onPbFilePressed();
    void onPbSaveXmlPressed();
    void updateHmi();
    void onPbAddButtonPressed();
    void onPbDelButtonPressed();
    void onPbLoadXmlPressed();
};

#endif // GENERATORPANEL_H
