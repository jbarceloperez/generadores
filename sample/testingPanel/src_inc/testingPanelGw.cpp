// File Name..................................testingPanel


#include "testingPanelGw.h"



testingPanelGw::testingPanelGw(BaseClass * parent)
: testingPanelQtCb(parent)
{

}

testingPanelGw::~testingPanelGw()
{

}
//------------------------------------------------------------------------------------
/*virtual*/ const ParameterLimitData* testingPanelGw::exportGetParameterLimit()
{
    return ConfigSignals::ParameterLimit_get().value_or(nullptr);
}
//-----------------------------------------------------------------------------------------
void testingPanelGw::exportAction(const Common::Action& p_action, const boost::any& p_any)
{
    //ControllerSignals::Action_cmd_id(p_action, p_any);
}
//-----------------------------------------------------------------------------------------
void testingPanelGw::exportMessage(const Format::MessageKind& p_kind, const Format::MessageBody& p_body)
{
    //ControllerSignals::Message_cmd_id(p_kind, p_body);
}
//------------------------------------------------------------------------------------
