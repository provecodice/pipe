#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        int n=0;
        int campi;
        close(piped1[1]);//figlio chiude piped1 lato scrittura
        close(piped2[0]);//figlio chiude piped2 lato lettura
        FILE *fp1;        
        char buffer[70];
        fp1=fopen("numeri.txt","r");
        int n1,n2,n3,n4,n5;
        while(fgets(buffer,64,fp1)!=NULL){
            campi=sscanf(buffer,"%d %d %d %d %d",&n1,&n2,&n3,&n4,&n5);
            valori[n].num1=n1;
            valori[n].num2=n2;
            valori[n].num3=n3;
            valori[n].num4=n4;
            valori[n].num5=n5;
            n=n+1;        
        }
        int i;
        for(i=0;i<n;i++){
            printf("%d %d %d %d %d\n",valori[i].num1,valori[i].num2,valori[i].num3,valori[i].num4,valori[i].num5);
        }   
        //il figlio invia i dati
        
        write(piped2[1],valori,sizeof(valori));//descrittore di scrittura 1
       
        



    }else{
        //processo padre
        int num1=0;
        int num2;
        int rilascio;
        numeri valori[10];
        close(piped1[0]);//il padre chiude il lato lettura
        close(piped2[1]);//figlio chiude piped lato scrittura       
        read(piped2[0],valori,sizeof(valori));//descrittore di scrittura 1
        printf("il figlio manda i num: %d %d %d %d %d\n",valori[0].num1,valori[0].num2,valori[0].num3,valori[0].num4,valori[0].num5);
             
        
       
        
       // read(piped2[0],&rilascio,sizeof(rilascio));
       // printf("il figlio manda il num: %d\n",rilascio);
        wait(&stato);
    }


}