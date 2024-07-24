#include "logs.hpp"

#include <math.h>
#include <stdlib.h>

class test_log {

public:
  test_log() : tracks("tracks"), hmi("hmi"), mainlog("main"), dsp("dsp") {}

  void run_test();

protected:
  dbg::log tracks;
  dbg::log hmi;
  dbg::log mainlog;
  dbg::log dsp;

  void run(unsigned int seed);
  static void * thread_run(void *);
};

void test_log::run_test() {
  dbg::scoped_log sl(hmi, dbg::str("%s:%d", __FUNCTION__, __LINE__));

  static const int MAX_THREADS = 20;
  pthread_t hilos[MAX_THREADS];

  for (int i=0; i<MAX_THREADS; i++)
    pthread_create(&hilos[i], NULL, thread_run, this);

  for (int i=0; i<MAX_THREADS; i++)
    pthread_join(hilos[i], NULL);
}


void * test_log::thread_run(void * param) {
  static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&mutex);
  unsigned int seed = rand();
  pthread_mutex_unlock(&mutex);
  
  test_log * tl = (test_log *)param;
  tl->run(seed);
  return NULL;
}

void test_log::run(unsigned int seed) {
  dbg::scoped_log sl(hmi, __AT__, dbg::log::INFO);

  for (int i = 0; i < 100; i++) {
    int j = rand() % 24;

    switch (j) {
    case 0: tracks.trace("Esto es una traza de depuracion detallada"); break;
    case 1: tracks.debug("Esto es una traza de depuracion somera"); break;
    case 2: tracks.info("Esto es una traza de informacion"); break;
    case 3: tracks.warning("Esto es una traza de atencion"); break;
    case 4: tracks.error("Esto es una traza de error"); break;
    case 5: tracks.critical("[%s] Esto es una traza de error critico", __AT__); break;
    case 6: hmi.trace("Esto es una traza de depuracion detallada"); break;
    case 7: hmi.debug("Esto es una traza de depuracion somera"); break;
    case 8: hmi.info("Esto es una traza de informacion"); break;
    case 9: hmi.warning("Esto es una traza de atencion"); break;
    case 10: hmi.error("Esto es una traza de error"); break;
    case 11: hmi.critical("[%s] Esto es una traza de error critico", __AT__); break;
    case 12: mainlog.trace("Esto es una traza de depuracion detallada"); break;
    case 13: mainlog.debug("Esto es una traza de depuracion somera"); break;
    case 14: mainlog.info("Esto es una traza de informacion"); break;
    case 15: mainlog.warning("Esto es una traza de atencion"); break;
    case 16: mainlog.error("Esto es una traza de error"); break;
    case 17: mainlog.critical("[%s] Esto es una traza de error critico", __AT__); break;
    case 18: dsp.trace("Esto es una traza de depuracion detallada"); break;
    case 19: dsp.debug("Esto es una traza de depuracion somera"); break;
    case 20: dsp.info("Esto es una traza de informacion"); break;
    case 21: dsp.warning("Esto es una traza de atencion"); break;
    case 22: dsp.error("Esto es una traza de error %d", 3); break;
    case 23: dsp.critical("[%s] Esto es una traza de error critico", __AT__); break;
    }
  }
}

int main(int argc, char * argv[])
{
  dbg::log::initialize();
  // system("xclock");
  test_log tl;

  tl.run_test();
}
