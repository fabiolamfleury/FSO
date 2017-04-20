#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include "output.h"
#include "pipe.h"

void sleepy_child(int *pipe){
  int i = 1;
  struct timeval elapsed_time;
  struct timeval initial_time;
  long int *times;

  gettimeofday(&initial_time,NULL);

  close (pipe[0]);
  FILE* stream;
  stream = fdopen (pipe[1], "w");

  while(1){
    gettimeofday(&elapsed_time, NULL);
    times = print_time_stamp(initial_time, elapsed_time, times);
    writer("do dorminhoco", times, i, stream);
    i++;
    sleep((rand() % 3));
  }

  close(pipe[1]);

}


void active_child(int *pipe){
  int i = 1;
  struct timeval elapsed_time;
  struct timeval initial_time;
  gettimeofday(&initial_time,NULL);

  close(pipe[0]);
  FILE* stream;
  stream = fdopen (pipe[1], "w");

  while(1){
    char message[180];
    printf("Digite mensagem: ");
    fgets(message, 180, stdin);
    message[strlen(message)-1]= '\0';
    gettimeofday(&elapsed_time, NULL);
    long int *times;
    times = print_time_stamp(initial_time, elapsed_time, times);
    char user[201] = "usuario: <";
    strcat(user, message);
    strcat(user, ">");
    writer(user, times, i, stream);
    i++;
  }

  close(pipe[1]);
}
