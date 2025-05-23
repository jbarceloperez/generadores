#include "panelcollection.h"
#include "../controller/controller.h"

PanelCollection::PanelCollection() {}

void PanelCollection::init()
{
    log = Controller::getInstance().getLogger();
}

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
        log->mainlog(TRACE, "PanelCollection::addPanel> Panel '" + p.getName() + "' alredy exists.");
    }
    else
        panelCollection.push_back(p);
}

void PanelCollection::delPanel(std::string panel)
{
    std::vector<GPanel>::iterator iter;
    for (iter = panelCollection.begin(); iter != panelCollection.end(); ) {
        if (!iter->getName().compare(panel))
        {
            iter = panelCollection.erase(iter);
            log->mainlog(TRACE, "PanelCollection::delPanel> Deleted panel " + panel + ".");
        }
        else
            ++iter;
    }
}

int PanelCollection::getLength()
{
    return panelCollection.size();
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

void PanelCollection::updateHeaders(SaesHeader *header)
{
    for (int j=0; j<panelCollection.size(); j++)
    {
        for(int i = 0; i < HeaderElement::NOELEMENTS; i++)
        {   
            HeaderElement elem = static_cast<HeaderElement>(i);
            if (header->getHeaderElement(elem) != "")
            {
                panelCollection[j].setHeaderElement(elem, header->getHeaderElement(elem));
            }
        }
    }
}
