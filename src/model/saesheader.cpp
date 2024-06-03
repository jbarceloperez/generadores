#include "saesheader.h"

SaesHeader::SaesHeader(string _fileName)
{
    for (int i = 0; i < NOELEMENTS; i++)
    {
        elements[i] = "";
    }
    elements[FILE_NAME] = _fileName;
}

string SaesHeader::getHeaderElement(HeaderElement element)
{
    return elements[element];
}

void SaesHeader::setHeaderElement(HeaderElement element, const string &value)
{
    elements[element] = value;
}

string SaesHeader::toString()
{
    string str = "";

    for (int i = 0; i < NOELEMENTS; i++)
    {
        if (elements[i] != "")
        {
            str += "// ";
            HeaderElement he = (HeaderElement) i;
            str += fillWithPoints(HeaderElementNameMap[he]);
            str += elements[i] + "\n";
        }
    }
    
    return str;
}

string SaesHeader::fillWithPoints(string str) {
    string newStr = str;
    for (int i = str.length(); i < 43; i++) {
        newStr += ".";
    }
    return newStr;
}
