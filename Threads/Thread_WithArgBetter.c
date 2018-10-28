
/*This program creates a thread and passes a function to it.
  The function takes one argument PASSED IN THE CORRECT WAY. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

void *PrintHello(void *);

int main() {
  pthread_t threads[NUM_THREADS];
  long intArgs[NUM_THREADS];
  int ret_value;
  long n, t;
  
  for(n=0; n<NUM_THREADS; n++){
	  intArgs[n] = n;
  }
  
  for(t=0; t<NUM_THREADS; t++){
    printf("Creating thread ...%ld\n", t);
    ret_value = pthread_create(&threads[t], NULL, PrintHello, (void *)&intArgs[t]);
    if (ret_value){
      printf("ERROR: return code from pthread_create() is %d\n", ret_value);
      exit(-1);
    }
  }
  
  pthread_exit(NULL);
  return 0;
}

void *PrintHello(void *thread_index) {
  long i;

  i = *((long *)thread_index);
  printf("Hello from thread %ld!\n", i);
  pthread_exit(NULL);

  return NULL;
}
