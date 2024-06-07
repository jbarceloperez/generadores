#include "logger.h"

Logger::Logger()
{
    hmi = dbg::log("hmi");
    mainlog = dbg::log("main");
    // alltraces = dbg::log("alltraces");
}

Logger::~Logger()
{

}

void Logger::log_hmi(TraceLevel level, char *msg)
{
    printTrace(&hmi, level, msg);
}

void Logger::log_mainlog(TraceLevel level, char *msg)
{
    printTrace(&mainlog, level, msg);
}

dbg::log *Logger::getHmi()
{
    return &hmi;
}

dbg::log *Logger::getMainlog()
{
    return &mainlog;
}


void Logger::printTrace(dbg::log *log, TraceLevel level, char *msg)
{
    switch (level)
        {
        case TRACE:
            log->trace(msg);
            break;
        case DEBUG:
            log->debug(msg);
            break;
        case INFO:
            log->info(msg);
            break;
        case WARNING:
            log->warning(msg);
            break;
        case ERROR:
            log->error("[%s] %s",__AT__,msg);
            break;
        case CRITICAL:
            log->critical("[%s] %s",__AT__,msg);
            break;
        
        default:
            break;
        }
}