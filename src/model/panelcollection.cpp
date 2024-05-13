#include "panelcollection.h"
#include "../controller.h"

void PanelCollection::addPanel(std::string name)
{
    addPanel(GPanel(name));
}

/**
 * Añade un panel nuevo a la colección si no existía previamente.
*/
void PanelCollection::addPanel(GPanel p)
{
    if (getPanelByName(p.getName()) != nullptr)
    {
        Controller::getInstance().printTrace(TRACE, "PanelCollection::addPanel> Panel '" + p.getName() + "' alredy exists.");
    }
    else
        panelCollection.push_back(p);
}

void PanelCollection::addPanelToGenerate(GPanel p)
{
    panelToGenerate.push_back(p);
}

/**
 * Retorna un puntero al panel con el nombre 'name'. Si no existe,
 * devuelve un puntero nulo.
*/
GPanel *PanelCollection::getPanelByName(std::string name)
{   
    GPanel* panelPointer = nullptr;
    for (auto & p : panelCollection) 
    {
        if (!p.getName().compare(name)) panelPointer = &p;
    }
    return panelPointer;
}

/**
 * Devuelve el panel corresponendiente a la posicion index. Si no
 * existe, devuelve nullptr.
*/
GPanel *PanelCollection::getPanelByIndex(int index)
{
    if(index < panelCollection.size())
    {
        return &panelCollection[index];
    }
    else return nullptr;
}

GPanel PanelCollection::getPanel(std::string name)
{
    for (auto & element : panelCollection) 
    {
        return element;
    }
}

bool PanelCollection::containsPanel(std::string name)
{
    for (GPanel p : panelCollection) {
        if (!p.getName().compare(name)) return true;        
    }
    return false;
}

std::vector<GPanel> PanelCollection::getVector() const
{
    return panelCollection;
}

std::vector<GPanel> PanelCollection::getVectorToGenerate() const
{
    return panelToGenerate;
}

std::vector<std::string> PanelCollection::getNames() const
{
    std::vector<std::string> v;
    for (GPanel p : panelCollection) {
        v.push_back(p.getName()); 
    }
    return v;
}

int PanelCollection::getPanelCollectionSize()
{
    return panelCollection.size();
}
