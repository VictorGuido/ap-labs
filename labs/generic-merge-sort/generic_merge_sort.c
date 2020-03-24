///Victor Jaret Guido Alvarado
//Generic mergesort
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


void funcMerge(char* arr[],int bot,int mid,int top) 
{
    int nL= mid-bot+1;
    int nR= top-mid;
    char** left=malloc(sizeof(char *)*nL);
    char** right=malloc(sizeof(char *)*nR);
    for(int i=0;i<nL;i++){ 
        left[i]=malloc(sizeof(arr[bot+i]));
        strcpy(left[i],arr[bot+i]);
    }
    for(int i=0;i<nR;i++){
        right[i]=malloc(sizeof(arr[mid+i+1])); 
        strcpy(right[i],arr[mid+i+1]);
    }
    int j=0;
    int k;
    int w=0;
    k=bot;
    while(w<nL&&j<nR){ 
        if(strcmp(left[w],right[j])<0){
            strcpy(arr[k++],left[w++]); 
        }
        else {
            strcpy(arr[k++],right[j++]);
        }
    }
    while(w<nL){
        strcpy(arr[k++],left[w++]);
    }
    while(j<nR){
        strcpy(arr[k++],right[j++]);
    }
}

void MergeSort(char* arr[],int bot,int top) 
{
    if(bot<top) 
    {
        int mid=(bot+top)/2; 
        MergeSort(arr,bot,mid);
        MergeSort(arr,mid+1,top);
        funcMerge(arr,bot,mid,top); 
    }
}

int main()
{
    printf("\nLongitud del arreglo a ordenar: ");
    int size;  
    scanf("%d",&size);
    char** arr= malloc(sizeof(char *)* size); 
    for(int i=0;i<size;i++){ 
        arr[i]=malloc(sizeof(char)*10); 
        printf("Introduce un elemento: ");
        scanf("%s",arr[i]);
    }
    MergeSort(arr,0,size-1);
    printf("\nEl arreglo ordenado es : ");
    printf("[");
    for(int i=0;i<size;i++){
        if(i == size-1){
            printf("%s] ",arr[i]);
        }
        else{
            printf("%s, ",arr[i]);
        }
    }
    return 0;
}


