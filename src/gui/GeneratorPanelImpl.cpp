#include "GeneratorPanelImpl.h"

#include "ui_GeneratorPanel.h"

#include "../controller.h"
#include <QFileDialog>
#include <QMessageBox>

class GeneratorPanelImpl::PrivateData
{
    public:
        PrivateData()
        {
        }

        ~PrivateData()
        {}

        Ui::GeneratorPanel ui;
};

GeneratorPanelImpl::GeneratorPanelImpl()
    : p_impl(new PrivateData())
{
    p_impl->ui.setupUi(this);

    // Conectar la señal clicked() de los botones a la ranura handleButtonClicked()
    connect(p_impl->ui.pbWithoutUI, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbWithUI, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbGenerate, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbAssociate, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbDeassociate, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbFile, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
}

GeneratorPanelImpl::~GeneratorPanelImpl()
{

}

void GeneratorPanelImpl::handleButtonClicked()
{
    if(sender() ==  p_impl->ui.pbWithUI)
    {
        Controller::getInstance().printTrace(DEBUG,"pbWithUi");
        QString file = p_impl->ui.lnePath->text();
        if (file.isEmpty())
        {
            QMessageBox::critical(this, "Error", "A .ui file must be selected.");
        }
        else 
        {
            Controller::getInstance().onPbWithUIPressed(file.toStdString());
        }
    }
    else if(sender() == p_impl->ui.pbWithoutUI)
    {
        Controller::getInstance().printTrace(DEBUG,"pbWithoutUi");
    }
    else if(sender() == p_impl->ui.pbGenerate)
    {
        Controller::getInstance().printTrace(DEBUG,"pbGenerate");
        Controller::getInstance().run();
    }
    else if(sender() == p_impl->ui.pbAssociate)
    {
        Controller::getInstance().printTrace(DEBUG,"pbAssociate");
    }
    else if(sender() == p_impl->ui.pbDeassociate)
    {
        Controller::getInstance().printTrace(DEBUG,"pbDeassociate");
    }
    else if(sender() == p_impl->ui.pbFile)
    {
        QString file = QFileDialog::getOpenFileName(this, "Select a ui file", "../");
        Controller::getInstance().onPbFilePressed(file.toStdString());
        p_impl->ui.lnePath->setText(file);
        Controller::getInstance().printTrace(INFO, "Selected file: " + file.toStdString());
    }
}
