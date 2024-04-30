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
    void onPbWithoutUIPressed();
    void onPbGeberatePressed();
    void onPbAssociatePressed();
    void onPbDeassociatePressed();
    void onPbFilePressed();
    void updateHmi();
};

#endif // GENERATORPANEL_H
