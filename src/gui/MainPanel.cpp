#include "MainPanel.h"
#include "ui_MainPanel.h"

#include "GeneratorPanelImpl.h"

MainPanel::MainPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPanel)
{
    ui->setupUi(this);

    // _panel.reset(new ScenarioWavRecordPanel());
    _panelGenerator.reset(new GeneratorPanelImpl);

    connect(ui->pbShow, &QPushButton::released, this, &MainPanel::slot_pb_released);
    connect(ui->pbHide, &QPushButton::released, this, &MainPanel::slot_pb_released);
}


MainPanel::~MainPanel()
{
    delete ui;

}

void MainPanel::slot_pb_released()
{
    if(sender() == ui->pbShow)
    {
        _panelGenerator->show();
    }
    else if(sender() == ui->pbHide)
    {
        _panelGenerator->hide();
    }

}
