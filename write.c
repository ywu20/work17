#include"write.h"

#define MEM 22222
#define SEM 11111
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

int main(){
  write_file("tele.txt");
}
