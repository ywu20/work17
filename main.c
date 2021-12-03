#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define SEM 11111
#define MEM 22222

void CREATE(){
  printf("creates\n");
}

void REMOVE(){
  printf("removes\n");
}
int main(int argc, char ** argv){
  // if arg is --create, creates the semaphore & shared memory
  // if arg is --remove, removes semaphore & shared memory
  if(argc){
    if(!strcmp(argv[1], "--create")){
      CREATE();
    }else if(!strcmp(argv[1],"--remove")){
      REMOVE();
    }

  }
  return 0;
}
