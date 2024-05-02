#ifndef PANELCOLLECTION_H
#define PANELCOLLECTION_H

#pragma once

#include "panel.h"
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
    GPanel* getPanelFromPanelCol(std::string name);
    GPanel getPanel(std::string name);
    bool containsPanel(std::string name);
    std::vector<GPanel> getVector() const;

};


#endif