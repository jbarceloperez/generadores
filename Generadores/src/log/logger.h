#ifndef LOGGER_H
#define LOGGER_H

#include "logs.hpp"
#include <string>

enum TraceLevel {
    TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL
};

/**
 * @class Logger
 * @brief Clase Logger que adapta la librería de logs de
 * SAES, e implementa dos objetos logger para separar las
 * trazas de la vista con las del resto de la aplicación.
 */ 
class Logger {

private:
    dbg::log hmi;
    dbg::log main;

public:
    Logger();

    void init(const char* config_file = "traces.cfg");
    void hmilog(TraceLevel level, const char* msg, ...);
    void mainlog(TraceLevel level, const char* msg, ...);
    void hmilog(TraceLevel level, std::string msg);
    void mainlog(TraceLevel level, std::string msg);
};

#endif  // LOGGER_H
