//Victor Jaret Guido Alvarado
//Mycat2

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <unistd.h>
#include <string.h>

/* filecopy:  copy file ifp to file ofp */
void filecopy(int ifp, int ofp){
  char line[255];
  int buf;
  while(1){
    buf=read(ifp,line,255);
    if(buf<=0){
      break;
    }
    else{
      write(ofp, line, buf);
    }
  }
}

/* cat:  concatenate files, version 2 */
int main(int argc, char *argv[])
{
    int fp;
    char *prog = argv[0];   ///program name for errors 
    if (argc == 1){  /// no args; copy standard input 
        filecopy(0, 1);
    }
    else{
      while (--argc > 0){
        fp = open(*++argv, O_RDONLY);
        if (fp == -1) {
          write(2, ": can′t open : ", 15);
          write(2, *argv, strlen(*argv));
          return 1;
        }
        else{
          filecopy(fp, 1);
          close(fp);
        }
      }
    }
    if (ferror(stdout)) {
      write(2, ": error writing stdout\n", 24);
      return 2;
    }
    return 0;
}
