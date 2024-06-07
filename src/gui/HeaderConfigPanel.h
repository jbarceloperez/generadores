#ifndef HEADERCONFIGPANEL_H
#define HEADERCONFIGPANEL_H

#pragma once

#include <QFrame>
#include "../controller/controller.h"

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

    void checkAll(bool checked);
    void clearAll();
    void save();
    // void iterateElements();
};

#endif // MAINWINDOW_H
