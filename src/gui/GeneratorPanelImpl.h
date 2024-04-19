#ifndef GENERATORPANELIMPL_H
#define GENERATORPANELIMPL_H

#pragma once

#include <QFrame>
#include <memory>


class GeneratorPanelImpl : public QFrame
{
public:
    GeneratorPanelImpl();
    ~GeneratorPanelImpl();

private:
    class PrivateData;
    std::unique_ptr<PrivateData> p_impl;
};

#endif // GENERATORPANEL_H
