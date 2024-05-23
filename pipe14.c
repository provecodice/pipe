#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pipep1f1[2];
    // creo la pipep1f1
    if(pipe(pipep1f1)<0){
        printf("errore creazione pipep1f1\n");
        exit(0);
    }
    int f1;
    int status1;
    f1=fork();
    if(f1==0){
        int rilascio;
        int perc;
        //sono nel processo figlio f1
        //figlio f1 chiude il lato scrittura
        close(pipep1f1[1]);
        read(pipep1f1[0],&rilascio,sizeof(rilascio));
        printf("[f1]il numero dhe mi invia il padr :%d\n",rilascio);
        read(pipep1f1[0],&perc,sizeof(perc));
        printf("[f1]il numero dhe mi invia il padr :%d\n",perc);

    }else{
        //sono nel processo padre p1
        //il padre p1 chiude lato lettura
        close(pipep1f1[0]);
        int num=1500;
        write(pipep1f1[1],&num,sizeof(num));
        int perc=50;
        write(pipep1f1[1],&perc,sizeof(perc));
        wait(&status1);
        

    }
   




}