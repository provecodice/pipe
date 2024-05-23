#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MSGSIZE 23
#define prigreco 3.14

typedef struct{
    char cognome[30];
    char nome[20];
    int voto;
    int classe;

}debiti;

int main(){
    debiti alunno;
    int day;
    int year;
    char weekday[20],month[20],dtm[100];
    strcpy(dtm,"venerdi aprile 12 2024");
    //printf("stampo il cintenuto di dtm:%s\n",dtm);
    sscanf(dtm,"%s %s %d %d",weekday,month,&day,&year);
    printf("%s %d,%d =%s\n",month,day,year,weekday);
    FILE *fp1;
    fp1=fopen("test1.txt","r");
    if(fp1==NULL){
        printf("errore\n");
        exit(0);
    }
    printf("tutto ok\n");
    int n=0;
    char buffer[90];
    int campi;
    char nome[40];
    int voto,classe;
    debiti alunni[15];
    while(fgets(buffer,64,fp1)!=NULL){
        campi=sscanf(buffer,"%s %d %d",nome,&voto,&classe);
        strcpy(alunni[n].nome,nome);
        alunni[n].voto=voto;
        alunni[n].classe=classe;
        n=n+1;        
    }
    int i;
    for(i=0;i<n;i++){

        printf("%s %d %d\n",alunni[n].nome,alunni[n].voto,alunni[n].classe);
    }


 
}