///Victor Jaret Guido Alvarado
//String library

#include <stdio.h>

char newString[150];


int main(int argc, char *argv[])
{
    printf("Initial Lenght      : %i",mystrlen(argv[1]));
    mystradd(argv[1],argv[2]);
    if(mystrfind(newString, argv[3])==-1){
        printf("\nSubstring was found: no\n");
    }
    else{
        printf("\nSubstring was found : yes\n");
    }
    return 0;
}
