#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

    int piped1[2];// canale 1
    int piped2[2];// canale 2
    int pid;
    int num;
    int stato;

    //creo la pipe 1
    if(pipe(piped1)<0){
        printf("errore creazione pipe1\n");
        exit(0);
    }
     //creo la pipe 2
    if(pipe(piped2)<0){
        printf("errore creazione pipe1\n");
        exit(0);
    }
    //creo il processo figlio
    pid=fork();
    if(pid<0){
        printf("errore creazione processo\n");
        exit(0);
    }
    if(pid==0){
        //processo figlio
        int rilascio;
        close(piped1[1]);//figlio chiude piped1 lato scrittura
        close(piped2[0]);//figlio chiude piped2 lato lettura
        for(int i=0;i<4;i++){
            read(piped1[0],&rilascio,sizeof(rilascio));
            printf("il padre manda il num: %d\n",rilascio);
        }
        
        rilascio=rilascio+1;
        write(piped2[1],&rilascio,sizeof(rilascio));//descrittore di scrittura 1
        sleep(4);
        printf("dopo sleep 10\n");



    }else{
        //processo padre
        int num1=0;
        int num2;
        int rilascio;
        close(piped1[0]);//il padre chiude il lato lettura
        close(piped2[1]);//figlio chiude piped lato scrittura
        for(int i=0;i<4;i++){
              write(piped1[1],&num1,sizeof(num));//descrittore di scrittura 1
              num1=num1+1;
        }
       
        
        read(piped2[0],&rilascio,sizeof(rilascio));
        printf("il figlio manda il num: %d\n",rilascio);
        wait(&stato);
    }


}