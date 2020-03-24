#include <string.h> 

extern char newString[150];

int mystrlen(char *str){
    int i =0;
    int count=0;
    while(str[i]!='\0'){ //aqui contamos que si haya caracter a leer
        i++;
        count++;
    }
    return count;
}

char *mystradd(char *origin, char *addition){ 
    int i = 0;
    int j = 0;
    printf("\nFirst string        : %s", origin); 
    printf("\nSecond string       : %s", addition); 
    while (origin[i] != '\0') { 
        newString[j] = origin[i]; 
        i++; 
        j++; 
    } 
    i = 0; 
    while (addition[i] != '\0') { 
        newString[j] = addition[i]; 
        i++; 
        j++; 
    } 
    newString[j] = '\0'; 
    printf("\nNew String          : %s", newString); 
}

int mystrfind(char *origin, char *substr){
    int M = mystrlen(substr); 
    int N = mystrlen(origin); 
    for (int i = 0; i <= N - M; i++) { 
        int j; 
        for (j = 0; j < M; j++){
            if (origin[i + j] != substr[j]){
                break; 
            }
        }
        if (j == M){ 
            return i;
        }
    } 
    return -1; 
}

