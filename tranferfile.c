#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int fd[2]; // File descriptors for the pipe
    pid_t pid;
    
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork(); // Create a child process
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) { // Child process
        close(fd[0]); // Close the read end of the pipe
        
        // Open the file to send
        FILE *file = fopen("numeri.txt", "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        
        char buffer[BUFFER_SIZE];
        size_t bytes_read;
        
        // Read from the file and write to the pipe
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            if (write(fd[1], buffer, bytes_read) != bytes_read) {
                perror("write");
               // exit(EXIT_FAILURE);
            }
        }
        
        // Close the write end of the pipe
        close(fd[1]);
        fclose(file);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(fd[1]); // Close the write end of the pipe
        
        // Create a buffer to read data from the pipe
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        
        // Read from the pipe and write to stdout
     
        while ((bytes_read = read(fd[0], buffer, sizeof(buffer))) > 0) {
            if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
                perror("write");
                //exit(EXIT_FAILURE);
            }           
        }

         /*
         printf("\n");
         while ((bytes_read = read(fd[0], buffer, sizeof(buffer))) > 0) {
                 campi=sscanf(buffer,"%d %s %d %d",&ord,nome,&num1,&num2);
                  printf("%s",buffer);
        }
        
*/
         
        // Close the read end of the pipe
        close(fd[0]);
        
        // Wait for the child process to finish
        wait(NULL);
    }
    
    return 0;
}
