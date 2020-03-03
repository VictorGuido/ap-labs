#include <stdio.h>

int main(){
    char c;
    char palabra[50];
    int contador = 0;
    while((c = getchar()) != EOF){
        if(c=='\n') {
            contador--;
            while(contador>=0) {
                printf("%c", palabra[contador--]);
            }
            contador = 0;
            printf("\n");
        }
        else {
            palabra[contador++]=c;
        }
    }    

    return 0;
}
