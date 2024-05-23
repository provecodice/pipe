#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int f1;
    int f2;
    int f3;
    int pidf1;
    int pidf2;
    int status1;
    int status2;
    int status3;
    int piped13[2];// canale 1
    int pipep1f1[2];// canale 1
    if(pipe(piped13)<0){
        printf("errore creazione pipe13\n");
        exit(0);
    }
     if(pipe(pipep1f1)<0){
        printf("errore creazione pipep1f1\n");
        exit(0);
    }
    f1=fork();
    if(f1==0){
        //sono dento il processo filgio f1
        //qui il mio codice per f1
        f3=fork();
        if(f3==0){
            //sono dentro il figlio f3
            printf("[f3] il mio pid:%d\n",getpid());
            //scrivo
            int num=10;
            close(piped13[0]);//il padre chiude il lato lettura
            write(piped13[1],&num,sizeof(num));//descrittore di scrittura 1
        }else{
            //sono dentro il figlio f1
            printf("[f1] il mio pid:%d\n",getpid());
            //leggo
            int rilascio;
            close(piped13[1]);//figlio chiude lato scrittura
            read(piped13[0],&rilascio,sizeof(int));
            printf("[f1] il figlio f3 manda il num %d\n",rilascio);
            int num=11;
            close(pipep1f1[0]);//il padre chiude il lato lettura
            write(pipep1f1[1],&num,sizeof(num));//descrittore di scrittura 1
            wait(&status3);
        }       
    }else{
        //sono dentro il processo padre p1
        f2=fork();
        if(f2==0){
            //sono dentro il pallino figlio f2
            //qui il mio codice per f2
            printf("[f2] il mio pid:%d\n",getpid());
            exit(2);
        }else{
            //sono dentro il porcesso padre p1
            //qui il mio codice per p1
             printf("[p1] il mio pid:%d\n",getpid());
             printf("[p1] il pid di mio padre:%d\n",getppid());
            int rilascio;
            close(pipep1f1[1]);//figlio chiude lato scrittura
            read(pipep1f1[0],&rilascio,sizeof(int));
            printf("[p1] il figlio f1 manda il num %d\n",rilascio);
             wait(&status1);
             wait(&status2);
        }
    }
}