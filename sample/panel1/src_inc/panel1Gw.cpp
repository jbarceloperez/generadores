// Company Name...............................SAES
// File Name..................................panel1


/**
 * @file panel1Gw.cpp
 * @brief Implementación de panel1Gw.
 * @details Fichero generado por generador de código de paneles.
 */

#include "panel1Gw.h"


panel1Gw::panel1Gw(BaseClass * parent)
: panel1QtCb(parent)
{

}

panel1Gw::~panel1Gw()
{

}
//------------------------------------------------------------------------------------
/*virtual*/ const ParameterLimitData* panel1Gw::exportGetParameterLimit()
{
    // return ConfigSignals::ParameterLimit_get().value_or(nullptr);    // TODO completar
    return 0;
}
//-----------------------------------------------------------------------------------------
void panel1Gw::exportAction(const Common::Action& p_action, const boost::any& p_any)
{
    //ControllerSignals::Action_cmd_id(p_action, p_any);     // TODO completar
}
//-----------------------------------------------------------------------------------------
void panel1Gw::exportMessage(const Format::MessageKind& p_kind, const Format::MessageBody& p_body)
{
    //ControllerSignals::Message_cmd_id(p_kind, p_body);    // TODO completar
}
//------------------------------------------------------------------------------------
