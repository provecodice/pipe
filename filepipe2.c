#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

typedef struct{
    char cognome[20];
    char nome[30];
    int voto;
    int media;
}alunni;

int main(){
    int fd1[2];
    int pid;
    alunni alunno[14];
    
    if (pipe(fd1) == -1) {
        printf("pipe error\n");
        exit(EXIT_FAILURE);
    }

    pid=fork();
    if(pid==0){
        close (fd1[0]);//close read
        //sono nel processo figlio
        FILE *file=fopen("testo2.txt","r");
        if(file==NULL){
             printf("file error\n");
        }
        size_t bytes_read;
        char buffer[BUFFER_SIZE];
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
           if(write(fd1[1],buffer,sizeof(buffer))!=bytes_read){
            printf("errore invio dati nellapipe");
            exit(EXIT_FAILURE);
           }
        }
    }else{
        //sono nel processo padre
        close(fd1[1]);//close write
        //leggo dalla pipe
        size_t bytes_read;
        char buffer[BUFFER_SIZE];
        
        char nome[20];
        char cognome[30];
        int voto;
        int media;
        int campi;
        int n=0;
        while ((bytes_read = read(fd1[0], buffer, sizeof(buffer))) > 0) {
                campi=sscanf(buffer,"%s %s %d %d",cognome,nome,&voto,&media);
                strcpy(alunno[n].cognome,cognome);
                strcpy(alunno[n].nome,nome);
                alunno[n].voto=voto;
                alunno[n].media=media;
                n=n+1;

        }    
        printf("\n");
        int i=0;        
        for(i=0;i<n;i++){
              printf("cognome %d:%s\n",i,alunno[i].cognome);
        }
    }
}

