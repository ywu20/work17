#include"write.h"

#define MEM 22222
#define SEM 11111



void write_file(char * file){

  // open file for read
  int rd = open(file, O_RDONLY);

  // get last line size
  int shmd = shmget(MEM, 0,0);
  int *size = shmat(shmd,0,0);


  // read last line
  char last_line[100];
  lseek(rd, *size * -1, SEEK_END);
  int a =read(rd, last_line, *size);

  printf("Last line of Telephone: %s\n",last_line);


  close(rd);

  // write to file new line
  int wr = open(file, O_WRONLY |O_APPEND);

  //read in the telephone line
  char line [100];
  printf("Enter your line of Telephone . . .\n");
  fgets(line, 100,stdin);

  // write into file
  lseek(wr, *size * -1, SEEK_END);
  write(wr,line, strlen(line));


  //store length in shared mem
  (*size)= strlen(line) +1;


  close(wr);

}

void sem(){
  // getting semaphore
  int semd = semget(SEM,1,0);

  // initialize sb
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;

  // take semaphore
  semop(semd, &sb, 1);
  printf("got the semaphore!\n");

  // do file writing ops
  write_file("tele.txt");

  // release semaphore
  sb.sem_op = 1;
  semop(semd, &sb, 1);

}

int main(){
  sem();
}
