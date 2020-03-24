#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct files 
{ 
   char name[50];
   char date1[50]; 
   char lastUpdate[50]; 
   int  updates; 
   char removalD[50]; 
};

struct files archivo1[1000];

char* itoa(int value, char* result, int base) {
	// check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }
		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;
		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );
		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
	return result;
}

void printer(int i, int r, int u){
  int fd1;
  int w = i-r;
  char buf[50];
  int up=0;
  int a =0;
  while(a<1000){
    if(archivo1[a].updates!=0){
      up++;
    }
    a++;
  }
  strcpy(buf, itoa(i,buf,10));
  fd1 = open("reportG.txt", O_WRONLY | O_CREAT, 0640);
  write(fd1, ("\nPacman Packages Report"), 23);
  write(fd1, ("\n----------------------"), 23);
  write(fd1, ("\n- Installed packages :"), 23);
  strcpy(buf, itoa(i,buf,10));
  write(fd1, buf, strlen(buf));
  write(fd1, ("\n- Removed packages :"), 21);
  strcpy(buf, itoa(r,buf,10));
  write(fd1, buf, strlen(buf));
  write(fd1, ("\n- Upgraded packages : "), 23);
  strcpy(buf, itoa(up,buf,10));
  write(fd1, buf, strlen(buf));
  write(fd1, ("\n- Current packages : "), 22);
  strcpy(buf, itoa(w,buf,10));
  write(fd1, buf, strlen(buf));
  write(fd1,"\n",1);
  close(fd1);
}

int installed=0;
int upgraded=0;
int removed=0;

int contador(char comp[]){
  if(strcmp(comp,"installed")==0){
    installed++;
    return installed;
  }
  if(strcmp(comp,"upgraded")==0){
    upgraded++;
    return upgraded;
  }
  if(strcmp(comp,"removed")==0){
    removed++;
    return removed;
  }
  return 0;
}

void instalacion(char line[]){
  int preC=0;
  int blanks=0;
  int iC=0;
  char compara[150];
  char name[50];
  char fechaI[100];
  strcpy(fechaI,"");
  strcpy(name,"");
  stpcpy(compara, "");
  stpcpy(compara, line);
  for(int i=0;i < sizeof(compara);i++){ 
    if(compara[i]== ' '){
      blanks++;
      if(blanks==4){
        preC=i;
      }
      if(blanks==5){
        for(int y=preC+1;y<i;y++){
          strncat(name, &compara[y],1);
        }
      }
    }
  }
  int a=0;
  while(compara[a]!=']'){
    strncat(fechaI, &compara[a],1);
    a++;
  }
  for(int w=0; w<sizeof(archivo1);w++){
    if(strcmp(archivo1[w].name, "")==0){
      strcpy(archivo1[w].name, name);
      strcpy(archivo1[w].date1, fechaI);
      break;
    }
  }
}

void remover(char line[]){
  char compara[150];
  stpcpy(compara, "");
  stpcpy(compara, line);  
  char fechaD[100];
  strcpy(fechaD,"");
  int a=0;
  while(compara[a]!=']'){
    strncat(fechaD, &compara[a],1);
    a++;
  }  
  int preC=0;
  int blanks=0;
  int iC=0;
  char name[50];
  char fechaI[100];
  strcpy(name,"");
  stpcpy(compara, "");
  stpcpy(compara, line);
  for(int i=0;i < sizeof(compara);i++){ 
    if(compara[i]== ' '){
      blanks++;
      if(blanks==4){
        preC=i;
      }
      if(blanks==5){
        for(int y=preC+1;y<i;y++){
          strncat(name, &compara[y],1);
        }
        //printf(" Nombre : %s", name);
      }
    }
  }
  for(int w=0; w<sizeof(archivo1);w++){
    if(strcmp(archivo1[w].name, name)==0){
      strcpy(archivo1[w].removalD, fechaD);
      break;
    }
  }
}

void upgrade(char line[]){
  char compara[150];
  stpcpy(compara, "");
  stpcpy(compara, line);  
  char fechaU[100];
  strcpy(fechaU,"");
  int a=0;
  int preC=0;
  int blanks=0;
  int iC=0;
  char name[50];
  char fechaI[100];
  strcpy(fechaI,"");
  strcpy(name,"");
  while(compara[a]!=']'){
    strncat(fechaU, &compara[a],1);
    a++;
  }
  for(int i=0;i < sizeof(compara);i++){ 
    if(compara[i]== ' '){
      blanks++;
      if(blanks==4){
        preC=i;
      }
      if(blanks==5){
        for(int y=preC+1;y<i;y++){
          strncat(name, &compara[y],1);
        }
      }
    }
  }
  for(int w=0; w<sizeof(archivo1);w++){
    if(strcmp(archivo1[w].name, name)==0){
      strcpy(archivo1[w].lastUpdate, fechaU);
      archivo1[w].updates = archivo1[w].updates+1;
      break;
    }
  }
}



void behaviour(char line[]){
  char compara[150];
  char behaviour[50];
  strcpy(behaviour,"");
  stpcpy(compara, "");
  stpcpy(compara, line);
  int preC=0;
  int blanks=0;
  int iC=0;
  char* b;
  for(int i=0;i < sizeof(compara);i++){
    if(compara[i]== ' '){
      blanks++;
      if(blanks==3){
        preC=i;
      }
      if(blanks==4){
        for(int y=preC+1;y<i;y++){
          strncat(behaviour, &compara[y],1);
        }
        if(strcmp(behaviour,"installed")==0){ 
          contador(behaviour);
          instalacion(compara);

        }
        if(strcmp(behaviour,"upgraded")==0){
          contador(behaviour);
          upgrade(compara);
        }
        if(strcmp(behaviour,"removed")==0){
          contador(behaviour);
          remover(compara);
        }
      }
    }
  }
}

void asiganV(){
  for(int i=0; i<sizeof(archivo1);i++){
    strcpy(archivo1[i].name,"");
    strcpy(archivo1[i].name,"");
    strcpy(archivo1[i].removalD,"");
    strcpy(archivo1[i].lastUpdate,"");
    strcpy(archivo1[i].date1,"");
    archivo1[i].updates=0;
  }
}

void resuF(){
  int fd1;
  char buf[50];
  int valor=0;
  fd1 = open("reportS.txt", O_WRONLY | O_CREAT, 0640);
  write(fd1, ("\nList of packages"), 17);
  write(fd1, ("\n---------------------"), 22);
  for(int i=0; i<sizeof(archivo1);i++){
    if(strcmp(archivo1[i].name,"")==0){
      break;
    }
    
    write(fd1, ("\n- Package name :"), 17);
    write(fd1, (archivo1[i].name), strlen(archivo1[i].name));
    write(fd1, ("\n  - Install date : "), 20);
    write(fd1, (archivo1[i].date1), strlen(archivo1[i].date1));
    write(fd1, ("\n  - Last Update : "), 19);
    write(fd1, (archivo1[i].lastUpdate), strlen(archivo1[i].lastUpdate));
    write(fd1, ("\n  - How many updates : "), 24);
    valor = archivo1[i].updates;
    strcpy(buf, itoa((valor),buf,10));
    write(fd1, buf, strlen(buf));
    write(fd1, ("\n  - Removal date : "), 20);
    write(fd1, (archivo1[i].removalD), strlen(archivo1[i].removalD));
  }
  close(fd1);
}

int main(int argc, char *argv[]){
  
  FILE * fPointer;
  fPointer = fopen(argv[1], "r");
  char line[150];
  int blank_counter =0;
  int prev_blank =0;
  int next_blank =0;
  int icounter=0;
  while(fgets(line,150,fPointer)!=NULL){
    for(int i=0; i<sizeof(line);i++){
        if(line[i]==' '){
          //printf("blank\n");
          blank_counter++;
          if(blank_counter==3){
              prev_blank=i;
          }
          if(blank_counter==4){
            next_blank=i;
          }
        }
        if(blank_counter==4){
            behaviour(line);
          break;
        }
    }
  }
  
  printer(contador("installed")-1,contador("removed")-1,contador("upgraded")-1);
  resuF();
  fclose(fPointer);
  printf("Generated 2 files");
  printf("\nreportG is a general report");
  printf("\nreportS is a specific report");
  return 0;
}
