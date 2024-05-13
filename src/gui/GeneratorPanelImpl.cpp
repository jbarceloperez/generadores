#include "GeneratorPanelImpl.h"

#include "ui_GeneratorPanel.h"

#include "../controller.h"
#include "../model/panel.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QListWidget>
#include <map>

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
    connect(p_impl->ui.pb_addButton, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pb_delButton, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    // Conectar la señal de la lista de paneles, para que actualice la info del currentPanel
    // connect(p_impl->ui.comboBox_panels, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectedPanel()));
    connect(p_impl->ui.listWidget_panels, SIGNAL(itemSelectionChanged()), this, SLOT(handleSelectedPanel()));
    
    for (int i = APPLY; i < NULLBUTTONACTION; i++)
    {
        p_impl->ui.listWidget_act->addItem(ButtonActionToString.find(static_cast<ButtonAction>(i))->second.data());
    }
}

GeneratorPanelImpl::~GeneratorPanelImpl()
{
    
}

void GeneratorPanelImpl::handleSelectedPanel()
{
    Controller::getInstance().printTrace(TRACE, "currentPanel list changed");

    int index = p_impl->ui.listWidget_panels->currentRow();
    Controller::getInstance().changeCurrentPanel(index);
    updateHmi();
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
    else if(sender() == p_impl->ui.pb_addButton)
    {
        onPbAddButtonPressed();
    }
    else if(sender() == p_impl->ui.pb_delButton)
    {
        onPbDelButtonPressed();
    }
    updateHmi();    // tras cada botón actualiza el ui
}

void GeneratorPanelImpl::onPbDelButtonPressed()
{
    Controller::getInstance().printTrace(TRACE, "pbDelButton");

    if (p_impl->ui.listWidget_but->selectedItems().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "No selected button.",QMessageBox::Ok);
        return;
    }
    int button = p_impl->ui.listWidget_but->currentItem()->listWidget()->row(p_impl->ui.listWidget_but->currentItem());
    Controller::getInstance().onPbDelButtonPressed(button);
}

void GeneratorPanelImpl::onPbAddButtonPressed()
{
    Controller::getInstance().printTrace(TRACE, "pbAddButton");
    if (p_impl->ui.cb_apply->isChecked())
        Controller::getInstance().onPbAddButtonPressed("pbApply", "QPushButton", "Apply");
    if (p_impl->ui.cb_cancel->isChecked())
        Controller::getInstance().onPbAddButtonPressed("pbCancel", "QPushButton", "Cancel");
    if (p_impl->ui.cb_check->isChecked())
        Controller::getInstance().onPbAddButtonPressed("pbCheck", "QPushButton", "Check");
    if (p_impl->ui.cb_reset->isChecked())
        Controller::getInstance().onPbAddButtonPressed("pbReset", "QPushButton", "Reset");
    if (p_impl->ui.cb_custom->isChecked())
        Controller::getInstance().onPbAddButtonPressed(p_impl->ui.lneCustom->text().toStdString(), "QPushButton", "Custom1");
}

void GeneratorPanelImpl::onPbFilePressed()
{
    QString file = QFileDialog::getOpenFileName(this, "Select a ui file", "../");
    
    // update ui
    p_impl->ui.lnePath->setText(file);
    Controller::getInstance().printTrace(INFO, "Selected file: " + file.toStdString());

}

void GeneratorPanelImpl::onPbDeassociatePressed()
{
    Controller::getInstance().printTrace(TRACE, "pbDeassociate");
    if (p_impl->ui.listWidget_but->selectedItems().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "No selected button.",QMessageBox::Ok);
        return;
    }
    int button = p_impl->ui.listWidget_but->currentRow();
    if (Controller::getInstance().onPbDeassociatePressed(button))
    {// update ui
        // updateTxtAssociate();
    }
}

void GeneratorPanelImpl::onPbAssociatePressed()
{
    Controller::getInstance().printTrace(TRACE, "pbAssociate");
    if (p_impl->ui.listWidget_act->selectedItems().size() == 0 || p_impl->ui.listWidget_but->selectedItems().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "No selected button.",QMessageBox::Ok);
        return;
    }
    int button = p_impl->ui.listWidget_but->currentRow();
    int action = p_impl->ui.listWidget_act->currentRow();
    if (Controller::getInstance().onPbAssociatePressed(button, action))
    {// update ui
        // updateTxtAssociate();
    }
}

void GeneratorPanelImpl::onPbXmlPressed()
{
    Controller::getInstance().printTrace(TRACE, "pbXml");
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
    Controller::getInstance().printTrace(TRACE, "pbGenerate");
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
    Controller::getInstance().printTrace(TRACE, "pbWithoutUi");
    QString name = p_impl->ui.lneName->text();
    if (name.isEmpty())
    {
        QMessageBox::critical(this, "Error", "You must set a name for the panel.");
    }
    else if (Controller::getInstance().onPbWithoutUIPressed(name.toStdString()))
    {   // actualizar lista paneles

        p_impl->ui.listWidget_panels->addItem(name);
        int index = p_impl->ui.listWidget_panels->count() - 1;
        p_impl->ui.listWidget_panels->setCurrentRow(index);
    }
    else QMessageBox::critical(this, "Error", "Panel alredy exists.");
}

void GeneratorPanelImpl::onPbWithUIPressed()
{
    Controller::getInstance().printTrace(TRACE, "pbWithUi");
    QString file = p_impl->ui.lnePath->text();
    if (file.isEmpty())
    {
        QMessageBox::critical(this, "Error", "A .ui file must be selected.");
    }
    else if (Controller::getInstance().onPbWithUIPressed(file.toStdString()))
    {   // actualizar combobox paneles
        const char* name = Controller::getInstance().getCurrentPanel()->getName().data();
        p_impl->ui.listWidget_panels->addItem(name);
        int index = p_impl->ui.listWidget_panels->count() - 1;
        p_impl->ui.listWidget_panels->setCurrentRow(index);
    }
    else QMessageBox::critical(this, "Error", "Panel alredy exists.");
}

void GeneratorPanelImpl::updateHmi()
{
    if (Controller::getInstance().getCurrentPanel() != nullptr)
    {
        updateButtons();
        updateTxtAssociate();
    }
}

void GeneratorPanelImpl::updateTxtAssociate()
{
    std::string str = Controller::getInstance().getPanelsInfo();
    p_impl->ui.txtAsociate->clear();
    p_impl->ui.txtAsociate->appendPlainText(str.data());
}

void GeneratorPanelImpl::updateButtons()
{
    p_impl->ui.listWidget_but->clear();
    for (Button b : Controller::getInstance().getCurrentPanel()->getButtons())
    {
        p_impl->ui.listWidget_but->addItem(b.getName().data());
    }
}