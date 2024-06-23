#include "GeneratorPanelImpl.h"

#include "ui_GeneratorPanel.h"

#include "../controller/controller.h"
#include "../model/gpanel.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QListWidget>
#include <QDir>
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
    headerPanel.reset(new HeaderConfigPanelImpl());
    controller = static_cast<GuiController*>(&Controller::getInstance());
    log = Controller::getInstance().getLogger();

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
    connect(p_impl->ui.pbCabecera, &QPushButton::clicked, this, &GeneratorPanelImpl::handleButtonClicked);
    // Conectar la señal de la lista de paneles, para que actualice la info del currentPanel
    connect(p_impl->ui.listWidget_panels, SIGNAL(itemSelectionChanged()), this, SLOT(handleSelectedPanel()));
    // Conectar la señal del combobox de los layout
    connect(p_impl->ui.comboLayout, SIGNAL(currentIndexChanged(int)), this, SLOT(handleLayoutCombobox()));
    // Conectar la señal de los spinBox del tamaño de los paneles
    connect(p_impl->ui.sbHeigth, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxHeight()));
    connect(p_impl->ui.sbWidth, SIGNAL(valueChanged(int)), this, SLOT(handleSpinBoxWidth()));    

    // añadir acciones de botones a la lista
    for (int i = APPLY; i < NULLBUTTONACTION; i++)
    {
        p_impl->ui.listWidget_act->addItem(ButtonActionToString[static_cast<ButtonAction>(i)].data());
    }
    // añadir los layout al combo
    for (int i = QHBOXLAYOUT; i < LayoutType::EXTERNAL_UI; i++)
    {   
        p_impl->ui.comboLayout->addItem(LayoutTypeToString[static_cast<LayoutType>(i)].data());
    }
}

GeneratorPanelImpl::~GeneratorPanelImpl()
{

}

void GeneratorPanelImpl::handleSpinBoxWidth()
{
    log->hmilog(TRACE,"currentPanel width changed");
    int w = p_impl->ui.sbWidth->value();
    if (controller->changeCurrentPanelWidth(w))
    {
        updateTxtAssociate();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Panel with external UI, cannot modify.",QMessageBox::Ok);
    }
}

void GeneratorPanelImpl::handleSpinBoxHeight()
{
    log->hmilog(TRACE, "currentPanel height changed");
    int h = p_impl->ui.sbHeigth->value();
    if (controller->changeCurrentPanelHeigth(h))
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
    log->hmilog(TRACE, "currentPanel list changed");

    int index = p_impl->ui.listWidget_panels->currentRow();
    controller->changeCurrentPanel(index);
    updateHmi();
}

void GeneratorPanelImpl::handleLayoutCombobox()
{
    log->hmilog(TRACE, "layout combobox changed");

    int index = p_impl->ui.comboLayout->currentIndex();
    if (controller->onComboPanelsChanged(index))
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
    else if(sender() == p_impl->ui.pbCabecera)
    {
        headerPanel->show();
        headerPanel->updateValues();
    }
}

void GeneratorPanelImpl::onPbDeletePanelPressed()
{
    log->hmilog(TRACE, "pbDeletePanel");
    int index = p_impl->ui.listWidget_panels->currentRow();
    if (index != -1)
    {
        string panel = p_impl->ui.listWidget_panels->currentItem()->text().toStdString();
        int panelesRestantes = controller->onPbDeletePanelPressed(panel);
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
        updateHmi();
    }
    else
    {
        log->hmilog(INFO, "No panel selected");
    }
}

void GeneratorPanelImpl::onPbDelButtonPressed()
{
    log->hmilog(TRACE, "pbDelButton");

    if (p_impl->ui.listWidget_but->selectedItems().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "No selected button.",QMessageBox::Ok);
        return;
    }
    int button = p_impl->ui.listWidget_but->currentItem()->listWidget()->row(p_impl->ui.listWidget_but->currentItem());
    controller->onPbDelButtonPressed(button);
    updateHmi();
}

void GeneratorPanelImpl::onPbAddButtonPressed()
{
    log->hmilog(TRACE, "pbAddButton");
    if (p_impl->ui.cb_apply->isChecked())
        controller->onPbAddButtonPressed("pbApply", "Apply");
    if (p_impl->ui.cb_cancel->isChecked())
        controller->onPbAddButtonPressed("pbCancel", "Cancel");
    // if (p_impl->ui.cb_check->isChecked())
    //     controller->onPbAddButtonPressed("pbCheck", "Check");
    if (p_impl->ui.cb_reset->isChecked())
        controller->onPbAddButtonPressed("pbReset", "Reset");
    if (p_impl->ui.cb_custom->isChecked())
        controller->onPbAddButtonPressed(p_impl->ui.lneCustom->text().toStdString(), "Custom1");
    updateHmi();
}

void GeneratorPanelImpl::onPbFilePressed()
{
    QString file = QFileDialog::getOpenFileName(this, "Select a ui file", "../");
    if (file.isEmpty())
    {
        log->hmilog(TRACE, "onPbFilePressed> No file selected.");
        return;
    }
    // update ui
    p_impl->ui.lnePath->setText(file);
    log->hmilog(INFO,"Selected file: %s", file.toStdString().data());
    updateHmi();
}

void GeneratorPanelImpl::onPbDeassociatePressed()
{
    log->hmilog(TRACE, "pbDeassociate");
    if (p_impl->ui.listWidget_but->selectedItems().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "No selected button.",QMessageBox::Ok);
        return;
    }
    int button = p_impl->ui.listWidget_but->currentRow();
    if (controller->onPbDeassociatePressed(button))
    {// update ui
        updateTxtAssociate();
    }
}

void GeneratorPanelImpl::onPbAssociatePressed()
{
    log->hmilog(TRACE, "pbAssociate");
    if (p_impl->ui.listWidget_act->selectedItems().size() == 0 || p_impl->ui.listWidget_but->selectedItems().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "No selected button.",QMessageBox::Ok);
        return;
    }
    int button = p_impl->ui.listWidget_but->currentRow();
    int action = p_impl->ui.listWidget_act->currentRow();
    if (controller->onPbAssociatePressed(button, action))
    {// update ui
        updateTxtAssociate();
    }
}

void GeneratorPanelImpl::onPbSaveXmlPressed()
{
    log->hmilog(TRACE, "pbSaveXml");
    QString saveFile = QFileDialog::getSaveFileName(this, "Save the file to...", "../index.xml", "XML files (*.xml);;Any (*)");
    if (saveFile.isEmpty())
    {
        log->hmilog(TRACE, "onPbSaveXmlPressed> No file selected.");
        return;
    }
    controller->onPbSaveXmlPressed(saveFile.toStdString());
    string msg = "XML config saved in '" + saveFile.toStdString() + "'.";
    QMessageBox::information(this, "Success", msg.data(), QMessageBox::Ok);
}

void GeneratorPanelImpl::onPbLoadXmlPressed()
{
    log->hmilog(TRACE, "pbLoadXml");
    QString file = QFileDialog::getOpenFileName(this, "Choose a file", "../");
    if (file.isEmpty())
    {
        log->hmilog(TRACE, "onPbLoadXmlPressed> No file selected.");
        return;
    }
    int addedPanels = controller->onPbLoadXmlPressed(file.toStdString());
    int aux = 0, length = controller->getPanelNames().size();
    for (string n : controller->getPanelNames())
    {   
        if (aux >= length-addedPanels)
            p_impl->ui.listWidget_panels->addItem(n.data());
        aux++;
    }
    p_impl->ui.listWidget_panels->setCurrentRow(length-addedPanels);   
    string msg = "Added " + to_string(addedPanels) + " panels succesfully.";
    QMessageBox::information(this, "Panels added", msg.data(), QMessageBox::Ok);    
    updateHmi();
}

void GeneratorPanelImpl::onPbGeberatePressed()
{
    log->hmilog(TRACE, "pbGenerate");
    QString dir_path = QFileDialog::getExistingDirectory(this, "Choose a directory to generate the code:", "../");
    if (dir_path.isEmpty())
    {
        log->hmilog(WARNING, "onPbGeneratePressed> No directory selected.");
        return;
    }
    QDir dir(dir_path);
    controller->onPbGeneratePressed(dir_path.toStdString());
    string msg = "Files succesfully generated in " + dir_path.toStdString() + ".";
    QMessageBox::information(this, "Files generated", msg.data(), QMessageBox::Ok);
}

void GeneratorPanelImpl::onPbWithoutUIPressed()
{
    log->hmilog(TRACE, "pbWithoutUi");
    QString name = p_impl->ui.lneName->text();
    if (name.isEmpty())
    {
        QMessageBox::critical(this, "Error", "You must set a name for the panel.");
    }
    else if (controller->onPbWithoutUIPressed(name.toStdString()))
    {   // actualizar lista paneles
        p_impl->ui.listWidget_panels->addItem(name);
        int index = p_impl->ui.listWidget_panels->count() - 1;
        p_impl->ui.listWidget_panels->setCurrentRow(index);
        updateHmi();
    }
    else QMessageBox::critical(this, "Error", "Panel alredy exists.");
}

void GeneratorPanelImpl::onPbWithUIPressed()
{
    log->hmilog(TRACE, "pbWithUi");
    QString file = p_impl->ui.lnePath->text();
    if (file.isEmpty())
    {
        QMessageBox::critical(this, "Error", "A .ui file must be selected.");
    }
    else if (controller->onPbWithUIPressed(file.toStdString()))
    {   // actualizar combobox paneles
        const char* name = controller->getCurrentPanel()->getName().data();
        p_impl->ui.listWidget_panels->addItem(name);
        int index = p_impl->ui.listWidget_panels->count() - 1;
        p_impl->ui.listWidget_panels->setCurrentRow(index);
        updateHmi();
    }
    else QMessageBox::critical(this, "Error", "Panel alredy exists.");
}

void GeneratorPanelImpl::updateHmi()
{
    updateButtons();
    updateTxtAssociate();
    updatePanelSettings();
}

void GeneratorPanelImpl::updateTxtAssociate()
{
    if (controller->getCurrentPanel() != nullptr)
    {
        std::string str = controller->panelInfo();
        p_impl->ui.txtAsociate->clear();
        p_impl->ui.txtAsociate->appendPlainText(str.data());
    }
}

void GeneratorPanelImpl::updateButtons()
{
    if (controller->getCurrentPanel() != nullptr)
    {
        p_impl->ui.listWidget_but->clear();
        for (GButton b : controller->getCurrentPanel()->getButtons())
        {
            p_impl->ui.listWidget_but->addItem(b.getName().data());
        }
    }
}

void GeneratorPanelImpl::updatePanelSettings()
{
    if (controller->getCurrentPanel() != nullptr)
    {
        if (controller->getCurrentPanel()->getLayout()!=EXTERNAL_UI)
        {
            int h = controller->getCurrentPanel()->getHeight();
            int w = controller->getCurrentPanel()->getWidth();
            p_impl->ui.sbHeigth->setValue(h);
            p_impl->ui.sbWidth->setValue(w);
        }
        LayoutType layout = controller->getCurrentPanel()->getLayout();
        p_impl->ui.comboLayout->setCurrentIndex(layout);
    }
}