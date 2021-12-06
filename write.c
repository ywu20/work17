#include"write.h"

#define MEM 22222
#define SEM 11111

/*
union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};
*/


void write_file(char * file){

  // open file for read
  int rd = open(file, O_RDONLY);

  // get last line size
  int shmd = shmget(MEM, 0,0);
  int *size = shmat(shmd,0,0);

  char last_line[100];
  int a =read(rd, last_line, *size);
  printf("Read %d bytes\n",a);
  printf("Size of last line: %d\n",*size);
  printf("The last line of the Telephone: %s\n",last_line);

  close(rd);

  int wr = open(file, O_TRUNC | O_WRONLY);

  //read in the telephone line
  char line [100];
  printf("Enter your line of Telephone . . .\n");
  fgets(line, 100,stdin);

  //store length in shared mem
  (*size)= strlen(line) +1;

  // write into file
  write(wr,line, 100);

  close(wr);

}

void sem(){
  int semd = semget(SEM,1,0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  semop(semd, &sb, 1);
  printf("got the semaphore!\n");
  write_file("tele.txt");

  sb.sem_op = 1;
  semop(semd, &sb, 1);

}

int main(){
  sem();
  //write_file("tele.txt");
}
