#ifndef _SAES_DEBUG_LOGS_
#define _SAES_DEBUG_LOGS_

#include <stdio.h>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <string.h>
#include <sys/time.h>

#ifdef TRACE
#undef TRACE
#endif

#ifdef ERROR
#undef ERROR
#endif

namespace dbg {

#ifdef NDEBUG

  // Release: No hacer nada
#define __AT__ ""

  class log {
  public:
    enum level_t { TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL };

    static void initialize(const char * = NULL) {}
    static void finalize(void) {}

    log() {}
    log(const char *) {}

    void setname(const char *) {}

    void trace(const char *, ...) const {}
    void debug(const char *, ...) const {}
    void info(const char *, ...) const {}
    void warning(const char *, ...) const {}
    void error(const char *, ...) const {}
    void critical(const char *, ...) const {}
  };

  class str {
  public:
    str(const char *, ...) {}
    operator const char *() { return ""; }
    const char * operator()() { return ""; }
  };

  class scoped_log {
  public:
    scoped_log(const log &, const char *, log::level_t = log::TRACE) {}
    ~scoped_log() {}
  };

  template <typename TYPE>
  std::string to_string(const TYPE &) { return ""; }

#else

  // Debug: Hacer todo
#define __FILE_TR__ ( strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __STRINGIFY__(x) #x
#define __TOSTRING__(x) __STRINGIFY__(x)
#define __AT__ (std::string(__FILE_TR__) + " +" + std::string(__TOSTRING__(__LINE__)) + ":" + std::string(__FUNCTION__)).c_str()

  class log {
  public:
    enum level_t { TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL };

    struct config_t {
      level_t level;
      FILE * out;
      pthread_mutex_t *mutex;

      config_t() : level(WARNING), out(stdout) {}
      config_t(level_t l, FILE * o, pthread_mutex_t & m) : level(l), out(o), mutex(&m) {}
    };

  protected:
    typedef std::map<std::string, config_t> logsmap_t;
    static logsmap_t logsmap;

    const char * name;
    config_t cfg;

    static void process_line(char * line);

  public:
    static void initialize(const char * cfg_file="traces.cfg");
    static void finalize(void);

    log();
    log(const char * name);

    void setname(const char *name);

    void trace(const char *, ...) const;
    void debug(const char *, ...) const;
    void info(const char *, ...) const;
    void warning(const char *, ...) const;
    void error(const char *, ...) const;
    void critical(const char *, ...) const;
  };

  class str {
  protected:
    char txt[1024];
  public:
    str(const char *, ...);
    operator const char *() const { return txt; }
    const char * operator()() const { return txt; }
    const char * c_str() const { return txt; }
  };

  class scoped_log {
  protected:
    const log & logger;
    char * text;
    log::level_t level;
    timeval ctor_time;

    void logtext(const char * prefix, const timeval * tv = NULL);
  public:
    scoped_log(const log & l, const char * t, log::level_t lvl = log::TRACE);
    ~scoped_log();
  };

  template <typename TYPE>
  std::string to_string(const TYPE & data) {
    std::stringstream ss;
    ss << data;
    return ss.str();
  }

#endif

}
#endif
