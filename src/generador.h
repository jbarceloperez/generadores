#ifndef GENERADOR_H
#define GENERADOR_H

#include "panel.h"
#include <filesystem>


void generateFiles(Panel p);
void generateFilesWithUi(Panel p);

std::string writeCmake(Panel p);




#endif  // GENERATOR_H
