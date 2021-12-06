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
  open("tele.txt", O_TRUNC | O_RDWR | O_CREAT, 0644);

  printf("Creating semaphore . . .\n");
  int semd = semget(SEM,1,IPC_CREAT | 0644);
  printf("sema pid : %d\n", semd);
  union semun us;
  us.val = 1;
  int r = semctl(semd, 0, SETVAL, us);

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
