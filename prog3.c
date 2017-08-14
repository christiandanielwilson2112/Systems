#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 1024
int main(int argc, char * argv[]){
	char buf[BUFSIZE] = {0};
	int z, x, a;
	char * ptr1, *ptr2;
	
	for(a = 1; a< argc; a++){
		int fd = open(argv[a], O_RDONLY);	
		if(fd < 0){
			perror("open error");
			return -1;
		}	

		while((z = read(fd, buf, BUFSIZE)) > 0){
			if (z == -1){
				perror("read error");
				return -1;
			}
			ptr1 = buf;
			for(ptr2 = strchr(buf, '\n'); ptr2 != NULL; ptr2 = strchr(ptr1, '\n')){
				int len = ptr2-ptr1+1;
				write(STDOUT_FILENO, ptr1, len);
				write(STDOUT_FILENO, "\n", 1);
				ptr1 = ptr2+1;
			}
			if(ptr2 == NULL){
				write(STDOUT_FILENO, ptr1, z-(ptr1-buf));
			}
		}
		close(fd);
	}
	return 0;
}
