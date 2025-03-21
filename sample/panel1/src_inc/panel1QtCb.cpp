// Company Name...............................SAES
// Project....................................HMI Code Generator
// Repository.................................https://elecsub@dev.azure.com/elecsub/Becarios%202024/_git/Generadores
// Author.....................................Javier Barceló
// Description................................Panel de muestra
// File Name..................................panel1
// Date.......................................25/07/2024


/**
 * @file panel1QtCb.cpp
 * @brief Implementación de panel1QtCb.
 * @details Fichero generado por generador de código de paneles.
 */

#include "panel1QtCb.h"
#include "ui_panel1.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

class panel1QtCb::PrivateData
{
    public:
        /**
         * @brief Constructor de la clase PrivateData.
         * @param parent Puntero al objeto BaseClass padre (nullptr por defecto).
         */
        PrivateData(BaseClass* parent)
        {

        }
        /**
         * @brief Destructor de la clase PrivateData.
         */
        ~PrivateData()
        {}      
        /**
         * UI del panel
         */
        Ui::panel1 ui;
};


panel1QtCb::panel1QtCb(BaseClass * parent)
    : BaseClass(parent)
    , p_impl(new PrivateData(parent))
{
    p_impl->ui.setupUi(this);

    initialize();

    signalsAndSlots();

}

panel1QtCb::~panel1QtCb()
{

}
//----------------------------------------------------------------
void panel1QtCb::init()
{
    const ParameterLimitData* limit = exportGetParameterLimit();
    if(limit)
    {

    }
}
//----------------------------------------------------------------
void panel1QtCb::initialize()
{   
    
    addFooterButton(Footer::Button_Apply, p_impl->ui.pbApply);

    addFooterButton(Footer::Button_Cancel, p_impl->ui.pbCancel);

    
    
    

    addComponents(p_impl->ui.layoutBase);
}

//----------------------------------------------------------------
void panel1QtCb::signalsAndSlots()
{

}


//----------------------------------------------------------------
bool panel1QtCb::panelCheck()
{
	// Implementation here
}

//----------------------------------------------------------------
void panel1QtCb::panelApply()
{
	// Implementation here
}

//----------------------------------------------------------------
void panel1QtCb::panelCancel()
{
	// Implementation here
}




//--------------------------------------------------------------------------------------------

