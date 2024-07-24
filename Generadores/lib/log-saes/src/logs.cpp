#ifndef NDEBUG

#ifdef __linux__

    #define __NORMAL__   "\e[0m"
    #define __INFO__     "\e[1m"
    #define __WARNING__  "\e[33m"
    #define __ERROR__    "\e[1;31m"
    #define __CRITICAL__ "\e[1;41;37m"

#elif defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)

    #include <windows.h>

    #define __NORMAL__   ""
    #define __INFO__     ""
    #define __WARNING__  ""
    #define __ERROR__    ""
    #define __CRITICAL__ ""

#endif // __UNIX__

#include "logs.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>

#include <sstream>
#include <fstream>
#include <string.h>

#include <pthread.h>

namespace dbg {

  static timeval start_time;

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
  static HANDLE hstdout;
#endif // _WIN32 || _WIN64

  void diff_timeval(timeval & now, const timeval & from) {
    if (now.tv_usec < from.tv_usec) {
      now.tv_usec += 1000000;
      now.tv_sec--;
    }

    now.tv_usec -= from.tv_usec;
    now.tv_sec -= from.tv_sec;
  }

  struct mutex_file_t {
    pthread_mutex_t mutex;
    FILE * file;
    mutex_file_t() : file(stdout) { pthread_mutex_init(&mutex, NULL); }
    mutex_file_t(FILE *f) : file(f) { pthread_mutex_init(&mutex, NULL); }
    ~mutex_file_t() { pthread_mutex_destroy(&mutex); }
  };

  static mutex_file_t std_out(stdout);
  static mutex_file_t std_err(stderr);

  log::logsmap_t log::logsmap;

  log::log() : name("noname"), cfg(WARNING, std_err.file, std_err.mutex) {
  }

  log::log(const char * n) : cfg(WARNING, std_err.file, std_err.mutex) {
    setname(n);
  }

  void log::setname(const char * n) {
    name = n;
    logsmap_t::iterator pos = logsmap.find(name);
    if (pos != logsmap.end()) cfg = pos->second;
  }

  void log::trace(const char *fmt, ...) const {
    if (cfg.level > TRACE) return;

    pthread_mutex_lock(cfg.mutex);

    timeval now;
    gettimeofday(&now, NULL);
    diff_timeval(now, start_time);

    fprintf(cfg.out, __NORMAL__ "%ld.%06ld %lX %s TRACE: ", now.tv_sec, now.tv_usec, (unsigned long int)pthread_self(), name);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cfg.out, fmt, ap);
    va_end(ap);
    fputc('\n', cfg.out);
    fflush(cfg.out);

    pthread_mutex_unlock(cfg.mutex);
  }

  void log::debug(const char *fmt, ...) const {
    if (cfg.level > DEBUG) return;

    pthread_mutex_lock(cfg.mutex);

    timeval now;
    gettimeofday(&now, NULL);
    diff_timeval(now, start_time);

    fprintf(cfg.out, __NORMAL__ "%ld.%06ld %lX %s DEBUG: ", now.tv_sec, now.tv_usec, (unsigned long int)pthread_self(), name);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cfg.out, fmt, ap);
    va_end(ap);
    fputc('\n', cfg.out);
    fflush(cfg.out);

    pthread_mutex_unlock(cfg.mutex);
  }

  void log::info(const char *fmt, ...) const {
    if (cfg.level > INFO) return;

    pthread_mutex_lock(cfg.mutex);

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    if (cfg.out == stdout) {
        GetConsoleScreenBufferInfo(hstdout, &csbiInfo);
        SetConsoleTextAttribute(hstdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
#endif // _WIN32 || _WIN64

    timeval now;
    gettimeofday(&now, NULL);
    diff_timeval(now, start_time);

    fprintf(cfg.out, __INFO__ "%ld.%06ld %lX %s INFO: ", now.tv_sec, now.tv_usec, (unsigned long int)pthread_self(), name);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cfg.out, fmt, ap);
    va_end(ap);
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    if (cfg.out == stdout) {
        // Restore the original text colors.
        SetConsoleTextAttribute(hstdout, csbiInfo.wAttributes);
    }
#endif // _WIN32 || _WIN64
    fprintf(cfg.out, __NORMAL__ "\n");
    fflush(cfg.out);

    pthread_mutex_unlock(cfg.mutex);
  }

  void log::warning(const char *fmt, ...) const {
    if (cfg.level > WARNING) return;

    pthread_mutex_lock(cfg.mutex);

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    if (cfg.out == stdout) {
        GetConsoleScreenBufferInfo(hstdout, &csbiInfo);
        SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }
#endif // _WIN32 || _WIN64

    timeval now;
    gettimeofday(&now, NULL);
    diff_timeval(now, start_time);

    fprintf(cfg.out, __WARNING__ "%ld.%06ld %lX %s WARNING: ", now.tv_sec, now.tv_usec, (unsigned long int)pthread_self(), name);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cfg.out, fmt, ap);
    va_end(ap);
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    if (cfg.out == stdout) {
        // Restore the original text colors.
        SetConsoleTextAttribute(hstdout, csbiInfo.wAttributes);
    }
#endif // _WIN32 || _WIN64

    fprintf(cfg.out, __NORMAL__ "\n");
    fflush(cfg.out);

    pthread_mutex_unlock(cfg.mutex);
  }

  void log::error(const char *fmt, ...) const {
    if (cfg.level > ERROR) return;

    pthread_mutex_lock(cfg.mutex);

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    if (cfg.out == stdout) {
        GetConsoleScreenBufferInfo(hstdout, &csbiInfo);
        SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
#endif // _WIN32 || _WIN64

    timeval now;
    gettimeofday(&now, NULL);
    diff_timeval(now, start_time);

    fprintf(cfg.out, __ERROR__ "%ld.%06ld %lX %s ERROR: ", now.tv_sec, now.tv_usec, (unsigned long int)pthread_self(), name);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cfg.out, fmt, ap);
    va_end(ap);
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    if (cfg.out == stdout) {
        // Restore the original text colors.
        SetConsoleTextAttribute(hstdout, csbiInfo.wAttributes);
    }
#endif // _WIN32 || _WIN64
    fprintf(cfg.out, __NORMAL__ "\n");
    fflush(cfg.out);

    pthread_mutex_unlock(cfg.mutex);
  }

  void log::critical(const char *fmt, ...) const {
    pthread_mutex_lock(cfg.mutex);

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    if (cfg.out == stdout) {
        GetConsoleScreenBufferInfo(hstdout, &csbiInfo);
        SetConsoleTextAttribute(hstdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);
    }
#endif // _WIN32 || _WIN64

    timeval now;
    gettimeofday(&now, NULL);
    diff_timeval(now, start_time);

    fprintf(cfg.out, __CRITICAL__ "%ld.%06ld %lX %s CRITICAL: ", now.tv_sec, now.tv_usec, (unsigned long int)pthread_self(), name);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cfg.out, fmt, ap);
    va_end(ap);
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    if (cfg.out == stdout) {
        // Restore the original text colors.
        SetConsoleTextAttribute(hstdout, csbiInfo.wAttributes);
    }
#endif // _WIN32 || _WIN64
    fprintf(cfg.out, __NORMAL__ "\n");
    fflush(cfg.out);

    pthread_mutex_unlock(cfg.mutex);
  }

  typedef std::map<std::string, mutex_file_t> filemap_t;
  static filemap_t openfiles;
  static const char * config_file;

  mutex_file_t * getFile(const char * filename) {
    filemap_t::iterator pos = openfiles.find(filename);
    // Si no existe, se crea y se incluye
    if (pos == openfiles.end()) {
      FILE * file = fopen(filename, "w");
      if (file == NULL) return NULL;
      mutex_file_t & result(openfiles[filename]);
      result.file = file;
      return &result;
    }
    // Si existe se devuelve ese
    return &pos->second;
  }

  log::level_t getLevel(const char * str) {
    if (strcmp(str, "TRACE") == 0) return log::TRACE;
    if (strcmp(str, "DEBUG") == 0) return log::DEBUG;
    if (strcmp(str, "INFO") == 0) return log::INFO;
    if (strcmp(str, "WARNING") == 0) return log::WARNING;
    if (strcmp(str, "ERROR") == 0) return log::ERROR;
    if (strcmp(str, "CRITICAL") == 0) return log::CRITICAL;
    return log::WARNING;
  }

  void log::process_line(char * line) {
    const char * logname = strtok(line, " \t\n");
    if (logname == NULL) return;

    const char * level = strtok(NULL, " \t\n");
    if (level == NULL) return;

    const char * output = strtok(NULL, " \t\n");
    if (output == NULL) return;

    mutex_file_t * mf;
    if (strcmp(output, "stdout")==0) mf = &std_out;
    else if (strcmp(output, "stderr")==0) mf = &std_err;
    else { // Es un fichero
      mf = getFile(output);
      if (mf == NULL) return;
    }

    // Aqui ya hay un fichero abierto y un nivel definido
    // Incluirlo en el mapa de ficheros de log
    logsmap[logname] = log::config_t(getLevel(level), mf->file, mf->mutex);
  }

  void log::initialize(const char *cfg_file) {

    gettimeofday(&start_time, NULL);

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
#endif // _WIN32 || _WIN64

    config_file = cfg_file;

    std::ifstream ifs(config_file);
    if (ifs.fail()) {
      fprintf(stderr, "Imposible abrir el fichero [%s]\n", config_file);
      return;
    }

    while (!ifs.eof()) {
      char line[256];
      ifs.getline(line, 256);

      switch (line[0]) {
      case 0: continue; // Linea vacia
      case '\n': continue; // Otra linea vacia
      case '#': continue; // Comentarios
      default: process_line(line);
      }
    }

    ifs.close();

    atexit(finalize);
  }

  void log::finalize(void) {
    // Cerrar todos los ficheros abiertos
    for (filemap_t::iterator i=openfiles.begin(); i!=openfiles.end(); i++) {
      fclose(i->second.file);
      i->second.file = NULL;
    }
  }

  void scoped_log::logtext(const char * prefix, const timeval * tv) {
    switch (level) {
    case log::TRACE:
      if (tv == NULL)
        logger.trace("%s %s", prefix, text);
      else
        logger.trace("%s %s (%ld.%06ld)", prefix, text, tv->tv_sec, tv->tv_usec);
      return;

    case log::DEBUG:
      if (tv == NULL)
        logger.debug("%s %s", prefix, text);
      else
        logger.debug("%s %s (%ld.%06ld)", prefix, text, tv->tv_sec, tv->tv_usec);
      return;

    case log::INFO:
      if (tv == NULL)
        logger.info("%s %s", prefix, text);
      else
        logger.info("%s %s (%ld.%06ld)", prefix, text, tv->tv_sec, tv->tv_usec);
      return;

    case log::WARNING:
      if (tv == NULL)
        logger.warning("%s %s", prefix, text);
      else
        logger.warning("%s %s (%ld.%06ld)", prefix, text, tv->tv_sec, tv->tv_usec);
      return;

    case log::ERROR:
      if (tv == NULL)
        logger.error("%s %s", prefix, text);
      else
        logger.error("%s %s (%ld.%06ld)", prefix, text, tv->tv_sec, tv->tv_usec);
      return;

    case log::CRITICAL:
      if (tv == NULL)
        logger.critical("%s %s", prefix, text);
      else
        logger.critical("%s %s (%ld.%06ld)", prefix, text, tv->tv_sec, tv->tv_usec);
      return;
    }
  }

  str::str(const char * fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(txt, 1024, fmt, ap);
    va_end(ap);
  }

  scoped_log::scoped_log(const log & l, const char * t, log::level_t lvl) : logger(l), text(strdup(t)), level(lvl) {
    gettimeofday(&ctor_time, NULL);
    logtext("->");
  }

  scoped_log::~scoped_log() {
    timeval now;
    gettimeofday(&now, NULL);
    diff_timeval(now, ctor_time);
    logtext("<-", &now);
    free(text);
  }

}

#endif
