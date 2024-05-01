#include "panelcollection.h"

void PanelCollection::addPanel(std::string name)
{
    panelCollection.push_back(GPanel(name));
}

void PanelCollection::addPanel(GPanel p)
{
    panelCollection.push_back(p);
}

GPanel *PanelCollection::getPanelFromPanelCol(std::string name)
{   
    GPanel* panelPointer = nullptr;
    for (auto & p : panelCollection) 
    {
        if (!p.getName().compare(name)) panelPointer = &p;
    }
    return panelPointer;
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
