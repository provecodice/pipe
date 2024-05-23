#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MSGSIZE 23

typedef struct{
    char cognome[20];
    char nome[30];
    int voto;
    int media;
}alunni;

int main(){
    alunni alunno[14];

    FILE *fp1;
    fp1=fopen("testo2.txt","r");
    if(fp1==NULL){
        printf("errore\n");
        exit(0);
    }
    printf("ok\n");
    char buffer[80];
    char nome[20];
    char cognome[30];
    int voto;
    int media;
    int campi;
    int n=0;
    while(fgets(buffer,64,fp1)!=NULL){
        campi=sscanf(buffer,"%s %s %d %d",cognome,nome,&voto,&media);
        strcpy(alunno[n].cognome,cognome);
         strcpy(alunno[n].nome,nome);
        alunno[n].voto=voto;
        alunno[n].media=media;
        n=n+1;
    }
    int i;
    for(i=0;i<n;i++){
          printf("%s %s %d %d\n",alunno[i].cognome,alunno[i].nome,alunno[i].voto,alunno[i].media);
    }
   int media1=(alunno[0].voto+alunno[0].media)/2;
   printf("trapani media:%d",media1);
}