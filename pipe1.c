#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct nodo{
    int numeri;
    struct nodo* punt;
}nodo;

int main(){
    nodo *l0, *scorri, *newel,*l1,*scorri1;
    l0=NULL;
    scorri=NULL;
    newel=NULL;
    int piped1[2];// canale 1
    int pid;
    int num;
    int stato;

    //creo la pipe 1
    if(pipe(piped1)<0){
        printf("errore creazione pipe1\n");
        exit(0);
    }
    //
    pid=fork();
    if(pid<0){
        printf("errore creazione processo\n");
        exit(0);
    }
    if(pid==0){
        //processo figlio
        int rilascio;
        close(piped1[1]);//figlio chiude lato scrittura
        read(piped1[0],&rilascio,sizeof(rilascio));
        printf("[f1] il pade manda il num %d\n",rilascio);
    }else{
        //processo padre
        int num1=10;
        close(piped1[0]);//il padre chiude il lato lettura
        //write(piped1[1],&num,sizeof(num));//descrittore di scrittura 1
        int num;
        for(int i=0;i<2;i++){
            printf("inserisci un numero:");
			scanf("%d", &num);
            newel = (nodo*)malloc(sizeof(nodo));
            newel->numeri=num;
            newel->punt=NULL;
            if(l0==NULL){
                    l0=newel;
           }else{
                scorri=l0;
                newel->punt=scorri;
                scorri=newel; 
                l0=scorri;
                }
        }

        write(piped1[1],&num1,sizeof(num1));//descrittore di scrittura 1
        scorri = l0;
	    while (scorri != NULL) {
		    printf("[p1] elemento:%d\n", scorri->numeri);
		    scorri = scorri->punt;
	    }
        wait(&stato);
    }
}