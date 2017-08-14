#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSZ 1024

int main (int argc, char * argv[])
  {
    int n, n2, fdin, fdin2, fdout;
    char buf[BUFSZ];
                       
    if (argc < 3 || (strcmp(argv[1], "-") == 0 && strcmp(argv[2], "-") == 0)) {
    write(STDERR_FILENO, "Usage: ", sizeof("Usage: "));
    write(STDERR_FILENO, argv[0], sizeof(argv[0]) - 1);
    write(STDERR_FILENO, " <file.in> <file.in> [<file.out>]\n", sizeof(" <file.in> <file.in> [<file.out>]\n"));
    exit(-1);
    }
                                         
    if(strcmp(argv[1], "-") == 0) 
        fdin = STDIN_FILENO;
    else 
        fdin = open(argv[1], O_RDONLY);

    if(fdin < 0) {
    perror(argv[1]);
    exit(-1);
    }
   
    if(strcmp(argv[2], "-") == 0) 
        fdin2 = STDIN_FILENO;   
    else      
        fdin2 = open(argv[2], O_RDONLY);
                                 
    if(fdin2 < 0) {
    perror(argv[2]);
    exit(-1);
    }
            
    if(argv[3])
        fdout = open(argv[3], O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0600);
    else 
        fdout = STDOUT_FILENO;

    while ((n = read(fdin, buf, BUFSZ)) > 0 ) {
    n = write(fdout,buf,n);
    if(n == -1) {
        printf("Write error\n");
        exit(-1);
    }
    }

     while ((n2 = read(fdin2, buf, BUFSZ)) > 0 ) {
     n2 = write(fdout,buf,n2);
     if(n2 == -1) {
        printf("Write error\n");
        exit(-1);
    }
    }
                                                                                                   
    if (n < 0) {
    perror(argv[1]);
    exit(-1);
    }
     
    close(fdin);
    close(fdin2);
    close(fdout);
    exit(0);
    }
