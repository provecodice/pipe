#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct drinks{
    int ord;
    char nome[20];
    int num1;
    int num2;
}drink;

int main(){
    drink alcolici[20];
    int p1[2];
    int p2[2];
    int f1;

    //
    if (pipe(p1)<0){
        printf("errore creazione pipe");
    }
     if (pipe(p2)<0){
        printf("errore creazione pipe");
    }
    if(f1=fork()==0){
        //sono dentro il processo figlio
        close(p1[0]);//pipe il lettura
        close(p2[1]);//pipe il scrittura
        FILE *fp1;
        fp1=fopen("cocktail.txt","r");
        if(fp1==NULL){
            printf("errore lettura\n");
        }
        printf("ok\n");
    char buffer[64];
    int campi;
    int ord;
    char nome[30];
    int num1;
    int num2;
    int n=0;
    while(fgets(buffer,64,fp1)){
        campi=sscanf(buffer,"%d %s %d %d",&ord,nome,&num1,&num2);
        alcolici[n].ord=ord;
        strcpy(alcolici[n].nome,nome);
        alcolici[n].num1=num1;
        alcolici[n].num2=num2;

        n=n+1;
    }
    int i;
    for(i=0;i<n;i++){
        printf("alcolico %d %s %d %d\n",alcolici[i].ord,alcolici[i].nome,alcolici[i].num1,alcolici[i].num2);
    }
   

    }else{
        //sono dentro il propcesso padre
        close(p1[1]);//pipe il scrittura
        close(p2[0]);//pipe il lettura

    }






}