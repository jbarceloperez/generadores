// File Name..................................testingPanel


#include "testingPanelQtCb.h"
#include "ui_testingPanel.h"


#include <QRegularExpression>
#include <QRegularExpressionValidator>



class testingPanelQtCb::PrivateData
{
    public:
        PrivateData(BaseClass* parent)
        {

        }

        ~PrivateData()
        {}      

        Ui::testingPanel ui;
};


testingPanelQtCb::testingPanelQtCb(BaseClass * parent)
    : BaseClass(parent)
    , p_impl(new PrivateData(parent))
{
    p_impl->ui.setupUi(this);

    initialize();

    signalsAndSlots();

}

testingPanelQtCb::~testingPanelQtCb()
{

}
//----------------------------------------------------------------
void testingPanelQtCb::init()
{
    const ParameterLimitData* limit = exportGetParameterLimit();
    if(limit)
    {

    }
}
//----------------------------------------------------------------
void testingPanelQtCb::initialize()
{   
    addFooterButton(Footer::Button_Apply, p_impl->ui.pbApply);

    addFooterButton(Footer::Button_Cancel, p_impl->ui.pbCancel);

    
    
    
    

    addComponents(p_impl->ui.generatedLayout);
}

//----------------------------------------------------------------
void testingPanelQtCb::signalsAndSlots()
{

}


//----------------------------------------------------------------
void testingPanelQtCb::panelApply()
{
	// Implementation here
}

//----------------------------------------------------------------
void testingPanelQtCb::panelCancel()
{
	// Implementation here
}




//--------------------------------------------------------------------------------------------

