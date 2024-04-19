#include "GeneratorPanelImpl.h"

#include "ui_GeneratorPanel.h"

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
}

GeneratorPanelImpl::~GeneratorPanelImpl()
{

}
