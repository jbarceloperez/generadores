#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <string>
#include <vector>
#include "xmlattribute.h"

using namespace std;

/**
 * Clase que representa un elemento del fichero XML. Tiene cadenas que 
 * representan el nombre y el valor del elemento, si lo tuviese. Además,
 * tiene dos colecciones, un es vector<XMLAttribute> que representa los
 * atributos del elemento, y otro vector<XMLElement> que representa los
 * hijos que pueda tener el elemento.
*/
class XMLElement {

private:
    vector<XMLAttribute> attributes;
    vector<XMLElement> elements;
    string name;
    string content;


public:
    XMLElement() {};
    XMLElement(string name, string content);
    XMLElement(string name, string content, vector<XMLAttribute> attributes, vector<XMLElement> elements);

    string getName() const;
    string getContent() const;
    vector<XMLAttribute> getAttributes();
    vector<XMLElement> getElements();

    string getAttributeValue(string name);
    XMLElement getSubelement(string name);
    void addSubelement(XMLElement elem);   
    void addAttribute(XMLAttribute attr); 
    void addAttribute(string name, string data);
    int numSubelements() const;
    string toString(int depth) const;
};

#endif