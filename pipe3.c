#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MSGSIZE 23

int main (){
 int pid, piped[2], stato;
 char inpbuf [MSGSIZE];
 char in;
 char* j[2]={"T"};
 const char* mes[3]={"hello","saluto errato","mandami un numero tra 0 e 24"};
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
    int num;
    close(piped[1]);/*figlio chiude lato scrittura*/
    read(piped[0], inpbuf,sizeof(inpbuf));//sizeof(char)
	  printf("figlio legge :%s\n", inpbuf);	
    printf("ins:numero");
    scanf("%d",&num);
    
 }else { 
 /* padre */ 
    close(piped[0]); /*padre chiude lato lettura*/
	write (piped[1], mes[1],sizeof(mes));//sizeof(char)
	wait(&stato); exit(0);
  }
}

