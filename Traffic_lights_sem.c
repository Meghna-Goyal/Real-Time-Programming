//Program for German traffic lights using Semaphores and Mutexes. Code for Raspberry Pi.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

// Our lamps:
//	(These are wiringPi pin numbers)

#define	RED		0
#define	YELLOW		1
#define	GREEN		2
#define	RED_MAN		3
#define	GREEN_MAN	4

sem_t sem1, sem2;

void *Traffic(void *);
void *Pedestrian(void *);

int main() 
{
pthread_t thread_Traffic;
pthread_t thread_Pedestrian;

sem_init(&sem1, 0, 0);
sem_init(&sem2, 0, 0);


 if (pthread_create (&thread_Traffic, NULL, Traffic, NULL)!=0) {
    printf("ERROR: Creation of thread_a\n");
    exit(-1);
  }

  if (pthread_create (&thread_Pedestrian, NULL, Pedestrian, NULL)!=0) {
    printf("ERROR: Creation of thread_b\n");
    exit(-1);
  }

if (pthread_join(thread_Traffic, NULL)!=0) {
    printf("ERROR: Joining of thread_a\n");
    exit(-1);
  }
  
  if (pthread_join(thread_Pedestrian, NULL)!=0) {
    printf("ERROR: Joining of thread_b\n");
    exit(-1);
  }
  sem_destroy(&sem1); //destroy semaphore
  sem_destroy(&sem2); 
  pthread_exit(NULL);               
  return(0);
} 


void *Traffic(){
  digitalWrite (GREEN,  1) ;
 printf ("Waiting for button ... ") ; fflush (stdout) ;
  while (digitalRead (BUTTON) == HIGH)
    delay (100) ;
  printf ("Got it\n") ; 
printf ("Stopping traffic ... ") ; fflush (stdout) ;
  digitalWrite (GREEN,  0) ;
  digitalWrite (YELLOW, 1) ;
  delay (2000) ;
  digitalWrite (YELLOW, 0) ;
  digitalWrite (RED,    1) ;
  delay (2000) ;
  printf ("StopPedestrian\n") ;
    sem_post(&sem1);
  digitalWrite (RED,    1) ;
  sem_wait (&sem2);
   digitalWrite (RED,    1) ;
  digitalWrite (YELLOW, 1) ;
  delay (2000) ;
    digitalWrite (GREEN,  1) ;	
}

void *Pedestrian(){
	{
  digitalWrite (RED_MAN,   1)
  sem_wait (&sem1);
  
  printf ("Walk now ... ") ; fflush (stdout) ;
  digitalWrite (RED_MAN,   0) ;
  digitalWrite (GREEN_MAN, 1) ;
  delay (10000) ;
  printf ("Walked\n") ;	
  digitalWrite (RED_MAN,   1) ;
  delay (5000) ;
  sem_post(&sem2);
  digitalWrite (RED_MAN,   1) ;

}
	
  	
	
