#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct numero{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
}numeri;

numeri valori[10];

int main() {
    int pipe1[2];
    int pipe2[2];
    int pid;
    int num;
    int stato;

    //creo la pipe1
    if(pipe(pipe1)<0){
        printf("Errore creazione pipe\n");
        exit(0);
    }

    //creo la pipe2
    if(pipe(pipe2)<0){
        printf("Errore creazione pipe\n");
        exit(0);
    }

    //creo il processo figlio
    pid = fork();
    if(pid<0){
        printf("Errore creazione");
    }   

    if(pid==0){
        //sono nel figlio
        int rilascio;
        int n =0;
        int campi;
        close(pipe1[1]);//chiudo puipe1 lato scrittura
        close(pipe2[0]);//chiudo pipe2 lato lettura
        FILE *fp1;
        fp1 = fopen("numeri.txt", "r");
        char buffer[70];
        int n1,n2,n3,n4,n5;
        while(fgets(buffer,64,fp1)){
            campi = sscanf(buffer, "%d %d %d %d %d", &n1,&n2,&n3,&n4,&n5);
            valori[n].num1 = n1;
            valori[n].num2 = n2;
            valori[n].num3 = n3;
            valori[n].num4 = n4;
            valori[n].num5 = n5;
            n++;
        }
        for(int i=0;i<n;i++){
            printf("%d %d %d %d %d\n", valori[i].num1, valori[i].num2,valori[i].num3,valori[i].num4,valori[i].num5);
        }
    }else{
        //sono nel padre
        int num1=0;
        int num2;
        int rilascio;
        close(pipe1[0]);//chiudo puipe1 lato lettura 
        close(pipe2[1]);//chiudo pipe2 lato scrittura

    }


}