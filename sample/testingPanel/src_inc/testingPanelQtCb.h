// File Name..................................testingPanel



/**
 * @file testingPanelQtCb.h
 * @brief Header para la clase testingPanelQtCb.
 * @details Fichero generado por generador de código de paneles.
 */
#ifndef __TESTINGPANELQTCB_H__
#define __TESTINGPANELQTCB_H__

#pragma once

#include <BaseClass.h>


class ParameterLimitData;

/**
 * @class testingPanelQtCb
 * @brief Clase que hereda de BaseClass, representa un panel con funcionalidad específica.
 */
class testingPanelQtCb : public BaseClass
{
    Q_OBJECT
public:
    /**
     * @brief Constructor de la clase testingPanelQtCb.
     * @param parent Puntero al objeto BaseClass padre (nullptr por defecto).
     */
    testingPanelQtCb(BaseClass* parent = 0);
    /**
     * @brief Destructor de la clase testingPanelQtCb.
     */
    virtual ~testingPanelQtCb();
    
    virtual void init() override final;
	/**
	 * @brief Método con la funcionalidad del botón \"Apply\".
	 */
	virtual void panelApply() override final;

	/**
	 * @brief Método con la funcionalidad del botón \"Cancel\".
	 */
	virtual void panelCancel() override final;






private Q_SLOTS:    


protected:
    virtual const ParameterLimitData* exportGetParameterLimit()=0;

private:
    /**
     * @brief Método para inicializar el panel. Añade la funcionalidad de
     * los botones y el layout. 
    */
    void initialize();
    /**
     * @brief Método para conectar los señales y slots.
    */
    void signalsAndSlots();    


private:
    /**
     * @brief Clase privada que contiene los datos privados del panel.
    */
    class PrivateData;
    /**
     * @brief Puntero al objeto PrivateData privado.
    */
    std::unique_ptr<PrivateData> p_impl;

};

#endif  // __TESTINGPANELQTCB_H__
