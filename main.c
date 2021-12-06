#include "write.h"


#define SEM 11111
#define MEM 22222

void CREATE(){
  printf("creates\n");
  printf("making shared memory ...\n");
  int shmd = shmget(MEM, sizeof(int), IPC_CREAT | 0644);
  int * size = shmat(shmd,0,0);
  *size = 0;

  printf("Creating file . . . \n");
  int fd = open("tele.txt", O_TRUNC | O_RDWR | O_CREAT, 0644);

  printf("Creating semaphore . . .\n");
  int semd = semget(SEM,1,IPC_CREAT | 0644);
  close(fd);
}

void REMOVE(){
  printf("removes\n");
  printf("Releasing shared memory . . . \n");
  int shmd = shmget(MEM, 0,0);
  shmctl(shmd,IPC_RMID,0);

  printf("Removing semaphore . . .\n");
  int semd = semget(SEM,1,0);
  semctl(semd, IPC_RMID,0);

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
