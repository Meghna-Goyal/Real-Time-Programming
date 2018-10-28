/*This program illustrates the use of an attribute object, 
the join function and the exit status values. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define NUM_THREADS 4

void *func1(void *);

int main() {
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  int ret_value;
  long t;
  void *status;

  //Initialize and set thread detached attribute
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(t=0; t<NUM_THREADS; t++) {
    printf("Creating thread %ld ...\n", t);
    ret_value = pthread_create(&threads[t], &attr, func1, (void *)t); 
    if (ret_value) {
      printf("ERROR; return code from pthread_create() is %d\n", ret_value);
      exit(-1);
    }
  }

  //Free attribute object
  pthread_attr_destroy(&attr);
  
  //Wait for all threads
  for(t=0; t<NUM_THREADS; t++) {
    ret_value = pthread_join(threads[t], &status);
    if (ret_value) {
      printf("ERROR: return code from pthread_join() is %d\n", ret_value);
      exit(-1);
    }
    printf("Completed join with thread %ld having a status of %ld\n",t,(long)status);
  }
 
  printf("Main program exits.\n");
  pthread_exit(NULL);
  return 0;
}


void *func1(void *arg) {
  int i;
  long num;
  double result=0.0;
  
  num = (long) arg;
  printf("Thread %ld starting...\n", num);
  for (i=0; i<100; i++) {
     result = result + pow((float)i,2);
  }
  printf("Thread %ld done. Result = %e\n", num, result);

  pthread_exit((void*) arg);
  return NULL;
}

