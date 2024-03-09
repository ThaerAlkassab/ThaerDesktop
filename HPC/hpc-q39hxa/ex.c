#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

void *printHello(void *threadid) {
  long tid;
  tid = (long)threadid;
  printf("Hello There! thread %ld, pthread ID - %lu\n", tid, pthread_self());
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;
  
  #pragma omp parallel for private(i) schedule(static,8)
  for (t = 0; t < NUM_THREADS; t++) {
    rc = pthread_create(&threads[t], NULL, printHello, (void *)t);
    if (rc) {
      printf("ERORR; return code from pthread_create() is %d\n", rc);
      exit(EXIT_FAILURE);
    }
  }
  pthread_exit(NULL);
}