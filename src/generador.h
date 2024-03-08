#ifndef GENERADOR_H
#define GENERADOR_H

#include "panel.h"
#include <filesystem>
#include <map>

enum FileToGenerate 
{
    HEADER, GWHEADER, GW, QTCBHEADER, QTCB, UI, CMAKELISTS, FILES_END
};

enum Mark
{
    NAME, NAME_CAPS
};

void generateFiles(Panel p);
void generateFilesWithUi(Panel p);

std::string writeFile(Panel p, map<std::string, std::string>& properties, FileToGenerate file);

std::string readTemplate(const std::string& filename);
void replaceMarks(std::string& code, const std::map<std::string, std::string>& properties);
void fillPropertiesMap(Panel p, map<std::string, std::string>& properties);


#endif  // GENERATOR_H
