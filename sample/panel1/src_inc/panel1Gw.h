// Company Name...............................SAES
// Project....................................HMI Code Generator
// Repository.................................https://elecsub@dev.azure.com/elecsub/Becarios%202024/_git/Generadores
// Author.....................................Javier Barceló
// Description................................Panel de muestra
// File Name..................................panel1
// Date.......................................25/07/2024


/**
 * @file panel1Gw.h
 * @brief Header para la clase panel1Gw.
 * @details Fichero generado por generador de código de paneles.
 */

#ifndef __PANEL1GW_H__
#define __PANEL1GW_H__

#pragma once

#include "panel1QtCb.h"

/**
 * @class panel1Gw
 * @brief Clase que hereda de panel1QtCb, implementa métodos para exportar mensajes y acciones
 */
class panel1Gw : public panel1QtCb
{
public:
    /**
     * @brief Constructor de la clase panel1Gw.
     * @param parent Puntero al objeto BaseClass padre (nullptr por defecto).
     */
    panel1Gw(BaseClass* parent = 0);
    /**
     * @brief Destructor de la clase panel1Gw.
     */
    virtual ~panel1Gw();

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

#endif  // __PANEL1GW_H__
