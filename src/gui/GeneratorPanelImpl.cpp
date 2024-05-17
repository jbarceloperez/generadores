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
    connect(p_impl->ui.pbSaveXml, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbLoadXml, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pb_addButton, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pb_delButton, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbDeletePanel, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    // Conectar la señal de la lista de paneles, para que actualice la info del currentPanel
    connect(p_impl->ui.listWidget_panels, SIGNAL(itemSelectionChanged()), this, SLOT(handleSelectedPanel()));
    // Conectar la señal del combobox de los layout
    connect(p_impl->ui.comboLayout, SIGNAL(currentIndexChanged(int)), this, SLOT(handleLayoutCombobox()));
    // Conectar la señal de los spinBox del tamaño de los paneles
    connect(p_impl->ui.sbHeigth, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxHeight()));
    connect(p_impl->ui.sbWidth, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxWidth()));    

    for (int i = APPLY; i < NULLBUTTONACTION; i++)
    {
        p_impl->ui.listWidget_act->addItem(ButtonActionToString.find(static_cast<ButtonAction>(i))->second.data());
    }
}

GeneratorPanelImpl::~GeneratorPanelImpl()
{

}

void GeneratorPanelImpl::handleSpinBoxWidth()
{
    Controller::getInstance().printTrace(TRACE, "currentPanel width changed");
    int h = Controller::getInstance().getCurrentPanel()->getHeight();
    int w = p_impl->ui.sbWidth->value();
    onSizeChanged(h,w);
}

void GeneratorPanelImpl::handleSpinBoxHeight()
{
    Controller::getInstance().printTrace(TRACE, "currentPanel height changed");
    int h = p_impl->ui.sbHeigth->value();
    int w = Controller::getInstance().getCurrentPanel()->getWidth();
    onSizeChanged(h,w);
}


void GeneratorPanelImpl::onSizeChanged(int h, int w)
{
    if (Controller::getInstance().changeCurrentPanelSize(h,w))
    {
        updateTxtAssociate();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Panel with external UI, cannot modify.",QMessageBox::Ok);
    }
}

void GeneratorPanelImpl::handleSelectedPanel()
{
    Controller::getInstance().printTrace(TRACE, "currentPanel list changed");

    int index = p_impl->ui.listWidget_panels->currentRow();
    Controller::getInstance().changeCurrentPanel(index);
    updateHmi();
}

void GeneratorPanelImpl::handleLayoutCombobox()
{
    Controller::getInstance().printTrace(TRACE, "layout combobox changed");

    int index = p_impl->ui.comboLayout->currentIndex();
    if (Controller::getInstance().onComboPanelsChanged(index))
        updateTxtAssociate();
    
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
    else if(sender() == p_impl->ui.pbSaveXml)
    {
        onPbSaveXmlPressed();
    }
    else if(sender() == p_impl->ui.pb_addButton)
    {
        onPbAddButtonPressed();
    }
    else if(sender() == p_impl->ui.pb_delButton)
    {
        onPbDelButtonPressed();
    }
    else if(sender() == p_impl->ui.pbLoadXml)
    {
        onPbLoadXmlPressed();
    }
    else if(sender() == p_impl->ui.pbDeletePanel)
    {
        onPbDeletePanelPressed();
    }
    updateHmi();    // tras cada botón actualiza el ui
}

void GeneratorPanelImpl::onPbDeletePanelPressed()
{
    Controller::getInstance().printTrace(TRACE, "pbDeletePanel");
    int index = p_impl->ui.listWidget_panels->currentRow();
    if (index != -1)
    {
        string panel = p_impl->ui.listWidget_panels->currentItem()->text().toStdString();
        int panelesRestantes = Controller::getInstance().onPbDeletePanelPressed(panel);
        // update panels
        QListWidgetItem *it = p_impl->ui.listWidget_panels->takeItem(p_impl->ui.listWidget_panels->currentRow());
        delete it;
        int index = p_impl->ui.listWidget_panels->count() - 1;
        p_impl->ui.listWidget_panels->setCurrentRow(index);
        if (panelesRestantes == 0)
        {
            p_impl->ui.listWidget_but->clear();
            p_impl->ui.txtAsociate->clear();
        }
    }
    else
    {
        Controller::getInstance().printTrace(INFO, "No panel selected");
    }
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
    if (file.isEmpty())
    {
        Controller::getInstance().printTrace(TRACE, "onPbFilePressed> No file selected.");
        return;
    }
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

void GeneratorPanelImpl::onPbSaveXmlPressed()
{
    Controller::getInstance().printTrace(TRACE, "pbSaveXml");
    QFileInfo check_file("input.xml");
    if (check_file.exists() && check_file.isFile())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Overwrite?", "'input.xml' alredy exists. Overwrite?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) return;
    }
    Controller::getInstance().onPbSaveXmlPressed();
    QMessageBox::information(this, "Success", "XML config saved in 'input.xml'.");
}

void GeneratorPanelImpl::onPbLoadXmlPressed()
{
    Controller::getInstance().printTrace(TRACE, "pbLoadXml");
    QString file = QFileDialog::getOpenFileName(this, "Choose a file", "../");
    if (file.isEmpty())
    {
        Controller::getInstance().printTrace(TRACE, "onPbLoadXmlPressed> No file selected.");
        return;
    }
    int addedPanels = Controller::getInstance().onPbLoadXmlPressed(file.toStdString());
    for (string n : Controller::getInstance().getPanelNames())
    {
        p_impl->ui.listWidget_panels->addItem(n.data());
    }
    p_impl->ui.listWidget_panels->setCurrentRow(0);   
    string msg = "Added " + to_string(addedPanels) + " panels succesfully.";
    QMessageBox::information(this, "Panels added", msg.data(), QMessageBox::Ok);    
}

void GeneratorPanelImpl::onPbGeberatePressed()
{
    Controller::getInstance().printTrace(TRACE, "pbGenerate");
    QFileInfo check_file("input.xml");
    // if (!check_file.exists() || !check_file.isFile())
    // {
    //     QMessageBox::warning(this, "Warning", "'input.xml' does not exist or is not a file.",QMessageBox::Ok);
    //     onPbSaveXmlPressed();
    // }
    onPbSaveXmlPressed();
    Controller::getInstance().onPbGeneratePressed();
    string msg = "Files succesfully generated in " + check_file.absolutePath().toStdString() + ".";
    QMessageBox::information(this, "Files generated", msg.data(), QMessageBox::Ok);
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
        updatePanelSettings();
    }
}

void GeneratorPanelImpl::updateTxtAssociate()
{
    std::string str = Controller::getInstance().panelInfo();
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

void GeneratorPanelImpl::updatePanelSettings()
{
    if (Controller::getInstance().getCurrentPanel()->getLayout()!=EXTERNAL_UI)
    {
        int h = Controller::getInstance().getCurrentPanel()->getHeight();
        int w = Controller::getInstance().getCurrentPanel()->getWidth();
        p_impl->ui.sbHeigth->setValue(h);
        p_impl->ui.sbWidth->setValue(w);
    }
    LayoutType layout = Controller::getInstance().getCurrentPanel()->getLayout();
    p_impl->ui.comboLayout->setCurrentIndex(layout);
}