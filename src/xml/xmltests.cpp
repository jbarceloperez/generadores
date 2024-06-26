#include <gtest/gtest.h>
#include "xmlattribute.h"
#include "xmlelement.h"
#include "xmlfile.h"
#include "xmlparser.h"


TEST(XMLTest, CorrectXMLRead) {
    XMLElement subelement1("subelment1", "");
    subelement1.addAttribute("atr", "123");
    XMLElement subelement2("subelment2", "¿hoolaaaa? ¿funciona?");
    XMLElement element("element", "");
    XMLAttribute attr("atr2", "456");
    element.addAttribute(attr);
    element.addSubelement(subelement1);
    element.addSubelement(subelement2);
    XMLFile f("/home/javi/test.xml", element);
    std::string expected = f.toString();
    XMLParser parser;
    XMLFile file = parser.readXml("/home/javi/test.xml");
    EXPECT_EQ(expected, file.toString());
}

/*
<?xml version="1.0" encoding="UTF-8"?>
<element atr2="456">
    <subelment1 atr="123"/>
    <subelment2>¿hoolaaaa? ¿funciona?</subelment2>
</element>
*/