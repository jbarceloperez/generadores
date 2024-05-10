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
    void onPbXmlPressed();
    void updateHmi();
    void onPbAddButtonPressed();
    void onPbDelButtonPressed();
};

#endif // GENERATORPANEL_H
