#include "GeneratorPanelImpl.h"

#include "ui_GeneratorPanel.h"

#include "../controller.h"
#include "../model/panel.h"
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

    p_impl->ui.comboBox_3->addItem(QString("panelApply"));
    p_impl->ui.comboBox_3->addItem(QString("panelCancel"));
    p_impl->ui.comboBox_3->addItem(QString("panelCheck"));
    p_impl->ui.comboBox_3->addItem(QString("panelReset"));
    p_impl->ui.comboBox_3->addItem(QString("panelCustom1"));
    p_impl->ui.comboBox_3->addItem(QString("panelCustom2"));
}

GeneratorPanelImpl::~GeneratorPanelImpl()
{

}

// TODO: Verificar si tiene sentido una unica funcion de update general,
// o una por botón que actualice solo lo necesario
void GeneratorPanelImpl::updateHmi()
{
}

void GeneratorPanelImpl::handleButtonClicked()
{
    if(sender() ==  p_impl->ui.pbWithUI)
    {
        onPbWithUIPressed();
    }
    else if(sender() == p_impl->ui.pbWithoutUI)
    {
        onPbWithoutUIPressed();
    }
    else if(sender() == p_impl->ui.pbGenerate)
    {
        onPbGeberatePressed();
    }
    else if(sender() == p_impl->ui.pbAssociate)
    {
        onPbAssociatePressed();
    }
    else if(sender() == p_impl->ui.pbDeassociate)
    {
        onPbDeassociatePressed();
    }
    else if(sender() == p_impl->ui.pbFile)
    {
        onPbFilePressed();
    }
    updateHmi();    // ¿?
}

void GeneratorPanelImpl::onPbFilePressed()
{
    QString file = QFileDialog::getOpenFileName(this, "Select a ui file", "../");
    Controller::getInstance().onPbFilePressed(file.toStdString());
    
    // update ui
    p_impl->ui.lnePath->setText(file);
    Controller::getInstance().printTrace(INFO, "Selected file: " + file.toStdString());

}

void GeneratorPanelImpl::onPbDeassociatePressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbDeassociate");
}

void GeneratorPanelImpl::onPbAssociatePressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbAssociate");
}

void GeneratorPanelImpl::onPbGeberatePressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbGenerate");
    Controller::getInstance().run();
}

void GeneratorPanelImpl::onPbWithoutUIPressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbWithoutUi");
}

void GeneratorPanelImpl::onPbWithUIPressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbWithUi");
    QString file = p_impl->ui.lnePath->text();
    if (file.isEmpty())
    {
        QMessageBox::critical(this, "Error", "A .ui file must be selected.");
    }
    else
    {
        if (Controller::getInstance().onPbWithUIPressed(file.toStdString()))
        {   // update ui if something new
            GPanel currentPanel = Controller::getInstance().getCurrentPanel();
            p_impl->ui.txtAsociate->appendPlainText(currentPanel.toString().data());
            for (Button b : currentPanel.getButtons())
            {
                p_impl->ui.comboBox_2->addItem(b.getName().data());
            }
        }
    }
}
