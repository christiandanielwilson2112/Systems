#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdio.h>
#define BUFSIZE 1024
int main(int argc, char * argv[]){
	char buf[BUFSIZE] = {0};
	int z, x;
	int fd = open(argv[1], O_RDONLY);	
	if(fd < 0){
		perror("open error");
		return -1;
	}	

	while((z = read(fd, buf, BUFSIZE)) > 0){
		if (z == -1){
			perror("read error");
			return -1;
		}
		x = write(STDOUT_FILENO, buf, z);
		if(x == -1 || x != z){
			perror("write error");
			return -1;
		}
	}
	close(fd);
	return 0;
}
