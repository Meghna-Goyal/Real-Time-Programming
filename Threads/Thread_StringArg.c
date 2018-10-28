/*This program creates a thread and passes a function to it.
  This function takes an argument, which is an element of an 
  array.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 7

void *PrintDay(void *);

char *days[NUM_THREADS];

int main() {
  pthread_t threads[NUM_THREADS];
  int *task_ids[NUM_THREADS];
  int ret_value, t;

  days[0] = "Monday";
  days[1] = "Tuesday";
  days[2] = "Wednesday";
  days[3] = "Thursday";
  days[4] = "Friday"; 
  days[5] = "Saturday";
  days[6] = "Sunday";
  
  for(t=0; t<NUM_THREADS; t++) {
    task_ids[t] = (int *) malloc(sizeof(int));
    *task_ids[t] = t;
    printf("Creating thread %d\n", t);
    ret_value = pthread_create(&threads[t], NULL, PrintDay, (void *) task_ids[t]);
    if (ret_value) {
      printf("ERROR: return code from pthread_create() is %d\n", ret_value);
      exit(-1);
    }
  }

  pthread_exit(NULL);
  return 0;
}


void *PrintDay(void *thread_index) {
  int *id_ptr, task_index;
  
  id_ptr = (int *) thread_index;
  task_index = *id_ptr;
  printf("Thread %d: %s\n", task_index, days[task_index]);

  pthread_exit(NULL); 
  return NULL;
}

