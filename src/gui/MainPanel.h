#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QWidget>
#include <memory.h>
// #include <ScenarioWavRecordPanel.h>

class GeneratorPanelImpl;

namespace Ui {
class MainPanel;
}

class MainPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MainPanel(QWidget *parent = 0);
    ~MainPanel();

private Q_SLOTS:
    void slot_pb_released();

private:
    Ui::MainPanel *ui;
    // std::unique_ptr<ScenarioWavRecordPanel> _panel;
    std::unique_ptr<GeneratorPanelImpl> _panelGenerator;
};

#endif // MAINPANEL_H
