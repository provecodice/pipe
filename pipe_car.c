#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MSGSIZE 23

int main (){
 int pid, piped[2], stato;
 char inpbuf [MSGSIZE];
 char in;
 char* j[2]={"T"};
 /* si crea una pipe */
 if(pipe(piped)<0) {
	 perror("piped"); 
	 exit(1);
 }
 if((pid=fork())<0){
	 perror("fork"); 
	 exit (2);
 }
 if(pid == 0) {  
 /* figlio */
    char car;
     char vett[20];
    close(piped[1]);/*figlio chiude lato scrittura*/
    //read(piped[0], &car,sizeof(car));//sizeof(char)
    read(piped[0], vett,sizeof(vett));//sizeof(char)
	printf("figlio legge :%s", vett);	
 }else { 
 /* padre */ 
    char car;
    car='w';
    char vett[20];
    strcpy(vett,"paolo");
    close(piped[0]); /*padre chiude lato lettura*/
	//write (piped[1], &car,sizeof(car));//sizeof(char)
    write (piped[1], vett,sizeof(vett));//sizeof(char)
	wait(&stato); exit(0);
  }

}

