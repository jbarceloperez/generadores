#include "logs.hpp"

enum TraceLevel {
    TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL
};

class Logger {

private:
    dbg::log hmi;
    dbg::log mainlog;
    void printTrace(dbg::log* log, TraceLevel level, char* msg);

public:
    Logger();
    ~Logger();

    void log_hmi(TraceLevel level, char* msg);
    void log_mainlog(TraceLevel level, char* msg);
    dbg::log* getHmi();
    dbg::log* getMainlog();

};
