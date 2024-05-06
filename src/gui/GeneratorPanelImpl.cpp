#include "GeneratorPanelImpl.h"

#include "ui_GeneratorPanel.h"

#include "../controller.h"
#include "../model/panel.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

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
    connect(p_impl->ui.pbXml, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);

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
    else if(sender() == p_impl->ui.pbXml)
    {
        onPbXmlPressed();
    }
    updateHmi();    // ¿?
}

void GeneratorPanelImpl::onPbFilePressed()
{
    QString file = QFileDialog::getOpenFileName(this, "Select a ui file", "../");
    // Controller::getInstance().onPbFilePressed(file.toStdString());   // pa qué
    
    // update ui
    p_impl->ui.lnePath->setText(file);
    Controller::getInstance().printTrace(INFO, "Selected file: " + file.toStdString());

}

void GeneratorPanelImpl::onPbDeassociatePressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbDeassociate");
    int button = p_impl->ui.comboBox_2->currentIndex();
    int action = p_impl->ui.comboBox_3->currentIndex();
    if (Controller::getInstance().onPbDeassociatePressed(button, action))
    {// update ui
        updateTxtAssociate();
    }
}

void GeneratorPanelImpl::onPbAssociatePressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbAssociate");
    int button = p_impl->ui.comboBox_2->currentIndex();
    int action = p_impl->ui.comboBox_3->currentIndex();
    if (Controller::getInstance().onPbAssociatePressed(button, action))
    {// update ui
        updateTxtAssociate();
    }
}

void GeneratorPanelImpl::onPbXmlPressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbXml");
    QFileInfo check_file("input.xml");
    if (check_file.exists() && check_file.isFile())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Overwrite?", "'input.xml' alredy exists. Overwrite?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) return;
    }
    Controller::getInstance().onPbXmlPressed();
    QMessageBox::information(this, "Success", "XML config saved in 'input.xml'.");
}


void GeneratorPanelImpl::onPbGeberatePressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbGenerate");
    QFileInfo check_file("input.xml");
    if (!check_file.exists() || !check_file.isFile())
    {
        QMessageBox::warning(this, "Warning", "'input.xml' does not exist or is not a file.",QMessageBox::Ok);
        return;
    }
    Controller::getInstance().onPbGeneratePressed();
}

void GeneratorPanelImpl::onPbWithoutUIPressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbWithoutUi");
    p_impl->ui.txtAsociate->clear();
}

void GeneratorPanelImpl::onPbWithUIPressed()
{
    Controller::getInstance().printTrace(DEBUG, "pbWithUi");
    QString file = p_impl->ui.lnePath->text();
    if (file.isEmpty())
    {
        QMessageBox::critical(this, "Error", "A .ui file must be selected.");
    }
    else if (Controller::getInstance().onPbWithUIPressed(file.toStdString()))
    { // update ui if something new
        updateTxtAssociate();
        for (Button b : Controller::getInstance().getCurrentPanel().getButtons())
        {
            p_impl->ui.comboBox_2->addItem(b.getName().data());
        }
    }
}

void GeneratorPanelImpl::updateTxtAssociate()
{
    GPanel currentPanel = Controller::getInstance().getCurrentPanel();
    p_impl->ui.txtAsociate->clear();
    p_impl->ui.txtAsociate->appendPlainText(currentPanel.toString().data());
}