#ifndef PANELCOLLECTION_H
#define PANELCOLLECTION_H

#pragma once

#include "gpanel.h"
#include <vector>
#include <string>

/**
 * Clase para manejar la colección de paneles del controlador
*/
class PanelCollection {

private:
    std::vector<GPanel> panelCollection;

public:
    PanelCollection() {}
    ~PanelCollection() {}

    void addPanel(std::string name);
    void addPanel(GPanel p);
    void delPanel(std::string panel);
    int getLength();
    GPanel* getPanelByName(std::string name);
    GPanel* getPanelByIndex(int index);
    bool containsPanel(std::string name);
    std::vector<GPanel> getVector() const;
    std::vector<std::string> getNames() const;
    int getPanelCollectionSize();
    void updateHeaders(SaesHeader *header);
};


#endif