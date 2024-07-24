#include "HeaderConfigPanel.h"
#include "../model/saesheader.h"
#include "../model/gpanel.h"
#include "ui_HeaderConfigPanel.h"

class HeaderConfigPanelImpl::PrivateData
{
    public:
        PrivateData()
        {
        }

        ~PrivateData()
        {}

        Ui::HeaderConfigPanel ui;
};

HeaderConfigPanelImpl::HeaderConfigPanelImpl()
    : p_impl(new PrivateData())
{
    p_impl->ui.setupUi(this);
    controller = static_cast<GuiController*>(&Controller::getInstance());
    log = Controller::getInstance().getLogger();

    connect(p_impl->ui.pbSave, &QPushButton::clicked, this, &HeaderConfigPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbCheckAll, &QPushButton::clicked, this, &HeaderConfigPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbUncheckAll, &QPushButton::clicked, this, &HeaderConfigPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbClearAll, &QPushButton::clicked, this, &HeaderConfigPanelImpl::handleButtonClicked);
    connect(p_impl->ui.pbSaveToAllPanels, &QPushButton::clicked, this, &HeaderConfigPanelImpl::handleButtonClicked);
    p_impl->ui.dateEdit->setDate(QDate::currentDate());

    updateValues();
}

HeaderConfigPanelImpl::~HeaderConfigPanelImpl()
{

}

void HeaderConfigPanelImpl::handleButtonClicked()
{
    if(sender() ==  p_impl->ui.pbCheckAll)
    {
        checkAll(true);
    }
    else if(sender() == p_impl->ui.pbUncheckAll)
    {
        checkAll(false);
    }
    else if(sender() == p_impl->ui.pbClearAll)
    {
        clearAll();
    }
    else if(sender() == p_impl->ui.pbSave)
    {
        save(false);
    }
    else if(sender() == p_impl->ui.pbSaveToAllPanels)
    {
        save(true);
    }
}

void HeaderConfigPanelImpl::updateValues()
{
    if (controller->getCurrentPanel() == nullptr)
    {
        return;
    }
    SaesHeader header = controller->getCurrentPanel()->getHeader();
    
    p_impl->ui.lne_companyName->setText(QString(header.getHeaderElement(COMPANY_NAME).data()));
    p_impl->ui.lne_project->setText(QString(header.getHeaderElement(PROJECT).data()));
    p_impl->ui.lne_csciName->setText(QString(header.getHeaderElement(CSCI_NAME).data()));
    p_impl->ui.lne_csciNumber->setText(QString(header.getHeaderElement(CSCI_NUMBER).data()));
    p_impl->ui.lne_cscsuname->setText(QString(header.getHeaderElement(CSC_SU_NAME).data()));
    p_impl->ui.lne_cscsunumber->setText(QString(header.getHeaderElement(CSC_SU_NUMBER).data()));
    p_impl->ui.lne_unitname->setText(QString(header.getHeaderElement(UNIT_NAME).data()));
    p_impl->ui.lne_unitnumber->setText(QString(header.getHeaderElement(UNIT_NUMBER).data()));
    p_impl->ui.lne_repository->setText(QString(header.getHeaderElement(REPOSITORY).data()));
    p_impl->ui.lne_designconsiderations->setText(QString(header.getHeaderElement(DESIGN_CONSIDERATIONS).data()));
    p_impl->ui.lne_constraints->setText(QString(header.getHeaderElement(CONSTRAINTS).data()));
    p_impl->ui.lne_detaileddesignref->setText(QString(header.getHeaderElement(DETAILED_DESIGN_REF).data()));
    p_impl->ui.lne_fullfilledrequirements->setText(QString(header.getHeaderElement(FULFILLED_REQUIREMENTS).data()));
    p_impl->ui.lne_uinittestsinfo->setText(QString(header.getHeaderElement(UNIT_TEST_INFORMATION).data()));
    p_impl->ui.lne_csciqualtestsinfo->setText(QString(header.getHeaderElement(CSCI_QUALIFICATION_TEST_INFORMATION).data()));
    p_impl->ui.lne_csctestsinfo->setText(QString(header.getHeaderElement(CSC_TEST_INFORMATION).data()));
    p_impl->ui.lne_datacreated->setText(QString(header.getHeaderElement(DATA_CREATED).data()));
    p_impl->ui.lne_author->setText(QString(header.getHeaderElement(AUTHOR).data()));
    p_impl->ui.lne_description->setText(QString(header.getHeaderElement(DESCRIPTION).data()));
    p_impl->ui.lne_filename->setText(QString(header.getHeaderElement(FILE_NAME).data()));
    p_impl->ui.lne_revisionhistory->setText(QString(header.getHeaderElement(REVISION_HISTORY).data()));
    p_impl->ui.dateEdit->setDate(QDate::fromString(header.getHeaderElement(DATE).data(), "dd/MM/yyyy"));
    p_impl->ui.lne_cp->setText(QString(header.getHeaderElement(CP).data()));
}

void HeaderConfigPanelImpl::checkAll(bool checked)
{
    p_impl->ui.companyName->setChecked(checked);
    p_impl->ui.project->setChecked(checked);
    p_impl->ui.csciName->setChecked(checked);
    p_impl->ui.csciNumber->setChecked(checked);
    p_impl->ui.cscsuname->setChecked(checked);
    p_impl->ui.cscsunumber->setChecked(checked);
    p_impl->ui.unitname->setChecked(checked);
    p_impl->ui.unitnumber->setChecked(checked);
    p_impl->ui.repository->setChecked(checked);
    p_impl->ui.designconsiderations->setChecked(checked);
    p_impl->ui.constraints->setChecked(checked);
    p_impl->ui.detaileddesignref->setChecked(checked);
    p_impl->ui.fullfillerequirements->setChecked(checked);
    p_impl->ui.unittestsinfo->setChecked(checked);
    p_impl->ui.csciqualtestsinfo->setChecked(checked);
    p_impl->ui.csctestsinfo->setChecked(checked);
    p_impl->ui.datacreated->setChecked(checked);
    p_impl->ui.author->setChecked(checked);
    p_impl->ui.description->setChecked(checked);
    p_impl->ui.filename->setChecked(checked);
    p_impl->ui.revisionhistory->setChecked(checked);
    p_impl->ui.date->setChecked(checked);
    p_impl->ui.cp->setChecked(checked);
}

void HeaderConfigPanelImpl::clearAll()
{
    log->hmilog(TRACE, "[" + string(__AT__) + "] pbClearAll");
    p_impl->ui.lne_companyName->setText("");
    p_impl->ui.lne_project->setText("");
    p_impl->ui.lne_csciName->setText("");
    p_impl->ui.lne_csciNumber->setText("");
    p_impl->ui.lne_cscsuname->setText("");
    p_impl->ui.lne_cscsunumber->setText("");
    p_impl->ui.lne_unitname->setText("");
    p_impl->ui.lne_unitnumber->setText("");
    p_impl->ui.lne_repository->setText("");
    p_impl->ui.lne_designconsiderations->setText("");
    p_impl->ui.lne_constraints->setText("");
    p_impl->ui.lne_detaileddesignref->setText("");
    p_impl->ui.lne_fullfilledrequirements->setText("");
    p_impl->ui.lne_uinittestsinfo->setText("");
    p_impl->ui.lne_csciqualtestsinfo->setText("");
    p_impl->ui.lne_csctestsinfo->setText("");
    p_impl->ui.lne_datacreated->setText("");
    p_impl->ui.lne_author->setText("");
    p_impl->ui.lne_description->setText("");
    p_impl->ui.lne_filename->setText("");
    p_impl->ui.lne_revisionhistory->setText("");
    p_impl->ui.dateEdit->setDate(QDate::fromString("01/01/2000", "dd/MM/yyyy"));
    p_impl->ui.lne_cp->setText("");
}

void HeaderConfigPanelImpl::save(bool saveToAllPanels)
{
    log->hmilog(TRACE, "[" + string(__AT__) + "] pbSave Header");    // debug
    SaesHeader header = SaesHeader("");

    if (p_impl->ui.companyName->isChecked()) header.setHeaderElement(COMPANY_NAME, p_impl->ui.lne_companyName->text().toStdString());
    if (p_impl->ui.project->isChecked()) header.setHeaderElement(PROJECT, p_impl->ui.lne_project->text().toStdString());
    if (p_impl->ui.csciName->isChecked()) header.setHeaderElement(CSCI_NAME, p_impl->ui.lne_csciName->text().toStdString());
    if (p_impl->ui.csciNumber->isChecked()) header.setHeaderElement(CSCI_NUMBER, p_impl->ui.lne_csciNumber->text().toStdString());
    if (p_impl->ui.cscsuname->isChecked()) header.setHeaderElement(CSC_SU_NAME, p_impl->ui.lne_cscsuname->text().toStdString());
    if (p_impl->ui.cscsunumber->isChecked()) header.setHeaderElement(CSC_SU_NUMBER, p_impl->ui.lne_cscsunumber->text().toStdString());
    if (p_impl->ui.unitname->isChecked()) header.setHeaderElement(UNIT_NAME, p_impl->ui.lne_unitname->text().toStdString());
    if (p_impl->ui.unitnumber->isChecked()) header.setHeaderElement(UNIT_NUMBER, p_impl->ui.lne_unitnumber->text().toStdString());
    if (p_impl->ui.repository->isChecked()) header.setHeaderElement(REPOSITORY, p_impl->ui.lne_repository->text().toStdString());
    if (p_impl->ui.designconsiderations->isChecked()) header.setHeaderElement(DESIGN_CONSIDERATIONS, p_impl->ui.lne_designconsiderations->text().toStdString());
    if (p_impl->ui.constraints->isChecked()) header.setHeaderElement(CONSTRAINTS, p_impl->ui.lne_constraints->text().toStdString());
    if (p_impl->ui.detaileddesignref->isChecked()) header.setHeaderElement(DETAILED_DESIGN_REF, p_impl->ui.lne_detaileddesignref->text().toStdString());
    if (p_impl->ui.fullfillerequirements->isChecked()) header.setHeaderElement(FULFILLED_REQUIREMENTS, p_impl->ui.lne_fullfilledrequirements->text().toStdString());
    if (p_impl->ui.unittestsinfo->isChecked()) header.setHeaderElement(UNIT_TEST_INFORMATION, p_impl->ui.lne_uinittestsinfo->text().toStdString());
    if (p_impl->ui.csciqualtestsinfo->isChecked()) header.setHeaderElement(CSCI_QUALIFICATION_TEST_INFORMATION, p_impl->ui.lne_csciqualtestsinfo->text().toStdString());
    if (p_impl->ui.csctestsinfo->isChecked()) header.setHeaderElement(CSC_TEST_INFORMATION, p_impl->ui.lne_csctestsinfo->text().toStdString());
    if (p_impl->ui.datacreated->isChecked()) header.setHeaderElement(DATA_CREATED, p_impl->ui.lne_datacreated->text().toStdString());
    if (p_impl->ui.author->isChecked()) header.setHeaderElement(AUTHOR, p_impl->ui.lne_author->text().toStdString());
    if (p_impl->ui.description->isChecked()) header.setHeaderElement(DESCRIPTION, p_impl->ui.lne_description->text().toStdString());
    if (p_impl->ui.filename->isChecked()) header.setHeaderElement(FILE_NAME, p_impl->ui.lne_filename->text().toStdString());
    if (p_impl->ui.revisionhistory->isChecked()) header.setHeaderElement(REVISION_HISTORY, p_impl->ui.lne_revisionhistory->text().toStdString());
    if (p_impl->ui.date->isChecked()) header.setHeaderElement(DATE, p_impl->ui.dateEdit->date().toString("dd/MM/yyyy").toStdString());
    if (p_impl->ui.cp->isChecked()) header.setHeaderElement(CP, p_impl->ui.lne_cp->text().toStdString());

    if (saveToAllPanels)
    {
        controller->onHeaderSaveToAllPanelsPressed(&header);
    }
    else
    {
        controller->onHeaderSavePressed(&header);
    }
    updateValues();
}
