#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFSIZE 1024

typedef struct{
	float z;
	float x; 
	float y;
}vector;

typedef struct{
	float mass;
	vector pos;
	vector vel;
}particle;

int main(int argc, char * argv[]){
	int count = 1;
	int r;
	particle * temp = (particle *)malloc(sizeof(particle));
	int fd = open(argv[1], O_RDONLY);
	
	while(r = read(fd, temp, sizeof(particle))){
		if(r != sizeof(particle)){
			printf("Error: Incomplete Record");
		}
		printf("Particle %d\n\tmass\t%f\n\tpos(%f,%f,%f)\n\tvel\t(%f,%f,%f)\n\n",count, temp->mass, temp->pos.x, temp->pos.y, temp->pos.z, temp->vel.x, temp->vel.y, temp->vel.z);
		count++;
	}
	
	return 0;

}  
