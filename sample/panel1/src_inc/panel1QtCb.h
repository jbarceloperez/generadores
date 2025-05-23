// Company Name...............................SAES
// Project....................................HMI Code Generator
// Repository.................................https://elecsub@dev.azure.com/elecsub/Becarios%202024/_git/Generadores
// Author.....................................Javier Barceló
// Description................................Panel de muestra
// File Name..................................panel1
// Date.......................................25/07/2024


/**
 * @file panel1QtCb.h
 * @brief Header para la clase panel1QtCb.
 * @details Fichero generado por generador de código de paneles.
 */
#ifndef __PANEL1QTCB_H__
#define __PANEL1QTCB_H__

#pragma once

#include <BaseClass.h>

class ParameterLimitData;

/**
 * @class panel1QtCb
 * @brief Clase que hereda de BaseClass, representa un panel con funcionalidad específica.
 */
class panel1QtCb : public BaseClass
{
    Q_OBJECT
public:
    /**
     * @brief Constructor de la clase panel1QtCb.
     * @param parent Puntero al objeto BaseClass padre (nullptr por defecto).
     */
    panel1QtCb(BaseClass* parent = 0);
    /**
     * @brief Destructor de la clase panel1QtCb.
     */
    virtual ~panel1QtCb();
    /**
     * @brief Método para inicializar el panel.
    */
    virtual void init() override final;
	/**
	 * @brief Método con la funcionalidad del botón "Apply".
	 */
	virtual void panelApply() override final;

	/**
	 * @brief Método con la funcionalidad del botón "Cancel".
	 */
	virtual void panelCancel() override final;

	/**
	 * @brief Método con la funcionalidad de checkear el panel.
	 */
	virtual bool panelCheck() override final;





private Q_SLOTS:    

protected:
    /**
     * @brief Método virtual puro a implementar en Gw.
    */
    virtual const ParameterLimitData* exportGetParameterLimit()=0;

private:
    /**
     * @brief Método para inicializar el panel. Añade la funcionalidad de
     * los botones y el layout. 
    */
    void initialize();
    /**
     * @brief Método para conectar los señales y funciones de slots.
    */
    void signalsAndSlots();    

private:
    /**
     * @class PrivateData
     * @brief Clase privada que contiene los datos privados del panel.
    */
    class PrivateData;
    /**
     * Puntero al objeto PrivateData privado.
    */
    std::unique_ptr<PrivateData> p_impl;

};

#endif  // __PANEL1QTCB_H__
