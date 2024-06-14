#ifndef HEADERCONFIGPANEL_H
#define HEADERCONFIGPANEL_H

#pragma once

#include <QFrame>
#include "../controller/guicontroller.h"

class HeaderConfigPanelImpl : public QFrame
{
    Q_OBJECT

public:
    HeaderConfigPanelImpl();
    ~HeaderConfigPanelImpl();
    void updateValues();

private slots:
    void handleButtonClicked();

private:
    class PrivateData;
    std::unique_ptr<PrivateData> p_impl;
    dbg::log loghmi;
    GuiController* controller;

    void checkAll(bool checked);
    void clearAll();
    void save(bool allPanels);
};

#endif // MAINWINDOW_H
