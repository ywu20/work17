#include "write.h"


#define SEM 11111
#define MEM 22222


union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};


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
  union semun us;
  us.val = 1;
  int r = semctl(semd, 0, SETVAL, us);
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

  printf("The story . . .\n");
  int fd = open("tele.txt", O_RDONLY);
  char str [1000];
  read(fd, str, 1000);
  printf("%s",str);

}
int main(int argc, char ** argv){
  // if arg is -c, creates the semaphore & shared memory
  // if arg is -r, removes semaphore & shared memory
  if(argc){
    if(!strcmp(argv[1], "-c")){
      CREATE();
    }else if(!strcmp(argv[1],"-r")){
      REMOVE();
    }

  }
  return 0;
}
