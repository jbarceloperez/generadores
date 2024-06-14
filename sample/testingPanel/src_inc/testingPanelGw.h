// File Name..................................testingPanel


/**
 * @file testingPanelGw.h
 * @brief Header para la clase testingPanelGw.
 * @details Fichero generado por generador de código de paneles.
 */
#ifndef __TESTINGPANELGW_H__
#define __TESTINGPANELGW_H__

#pragma once

#include "testingPanelQtCb.h"

class testingPanelGw : public testingPanelQtCb
{
public:
    /**
     * @brief Constructor de la clase testingPanelGw.
     * @param parent Puntero al objeto BaseClass padre (nullptr por defecto).
     */
    testingPanelGw(BaseClass* parent = 0);
    /**
     * @brief Destructor de la clase testingPanelGw.
     */
    virtual ~testingPanelGw();

protected:
    /**
     * @brief Info del método exportGetParameterLimit()
     * @return devuelve un puntero a un objeto de tipo ParameterLimitData
    */
    virtual const ParameterLimitData* exportGetParameterLimit()override final;
    /**
     * @brief Info del método exportAction()
    */
    virtual void exportAction(const Common::Action& , const boost::any&)override final;
    /**
     * @brief Info del método exportMessage()
    */
    virtual void exportMessage(const Format::MessageKind&, const Format::MessageBody&)override final;    

};

#endif  // __TESTINGPANELGW_H__
