#include "logger.h"
#include <cstdarg>

Logger::Logger() {}

/**
 * @brief Inicializa el logger con la configuración del archivo config_file,
 * y también inicializa los dos objetos logger hmi y main.
 * @param config_file ruta al archivo de configuración, por defecto es "traces.cfg"
*/
void Logger::init(const char *config_file)
{
    dbg::log::initialize(config_file);
    hmi = dbg::log("hmi");
    main = dbg::log("main");
}

/**
 * @brief Escribe un mensaje en el logger hmi.
 * @param level nivel de trace
 * @param msg mensaje a escribir
*/
void Logger::hmilog(TraceLevel level, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    switch (level)
    {
        case TRACE:
            hmi.trace(msg);
            break;
        case DEBUG:
            hmi.debug(msg);
            break;
        case INFO:
            hmi.info(msg);
            break;
        case WARNING:
            hmi.warning(msg);
            break;
        case ERROR:
            hmi.error(msg);
            break;
        case CRITICAL:
            hmi.critical(msg);
            break;
        default:
            break;
    }
    va_end(args);
}

/**
 * @brief Escribe un mensaje en el logger main.
 * @param level nivel de trace
 * @param msg mensaje a escribir
*/
void Logger::mainlog(TraceLevel level, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    switch (level)
    {
        case TRACE:
            main.trace(msg);
            break;
        case DEBUG:
            main.debug(msg);
            break;
        case INFO:
            main.info(msg);
            break;
        case WARNING:
            main.warning(msg);
            break;
        case ERROR:
            main.error(msg);
            break;
        case CRITICAL:
            main.critical(msg);
            break;
        default:
            break;
    }
    va_end(args);
}

void Logger::hmilog(TraceLevel level, std::string msg)
{
    hmilog(level, msg.c_str());
}

void Logger::mainlog(TraceLevel level, std::string msg)
{
    mainlog(level, msg.c_str());
}
