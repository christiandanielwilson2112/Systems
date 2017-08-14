#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include "logprt.h"

int main(int argc, char* argv[]) {
    
    if(argc !=2){
        printf("Usage: logprt network*.log\n");
        exit(-1);
    }

    char *buf[BUFSIZ];
    struct pcap_file_header head;
    int curpkt = 0;
    int hpk;
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror(argv[1]);
        exit(-1);
    }

    hpk = read(fd, &head, 24);
    if(hpk < 0) {
        perror("Read Error");
        exit(-1);
    }

    if(head.magic == PCAP_MAGIC) {
        printf("PCAP_MAGIC\n");
    } else if(head.magic == PCAP_SWAPPED_MAGIC) {
        printf("PCAP_SWAPPED_MAGIC\n");
    } else if(head.magic == PCAP_MODIFIED_MAGIC) {
        printf("PCAP_MODIFIED_MAGIC\n");
    } else if(head.magic == PCAP_SWAPPED_MODIFIED_MAGIC) {
        printf("PCAP_SWAPPED_MODIFIED_MAGIC\n");
    }else {
        printf("UNRECOGNIZED\n");
    }

    printf("Version major number = %d\n", head.version_major);
    printf("Version minor number = %d\n", head.version_minor);
    printf("GMT to local correction = %d\n", head.thiszone);
    printf("Timestamp accuracy = %d\n", head.sigfigs);
    printf("Snaplen = %d\n", head.snaplen);
    printf("Linktype = %d\n\n", head.linktype);

    unsigned int b_sec, c_sec;
    int b_usec, c_usec;
    int firsttime = 1;

    struct my_pkthdr mypk;
    while((hpk = read(fd,&mypk,sizeof(mypk))) > 0) {

        if(firsttime){
            firsttime = 0;
            b_sec = mypk.ts.tv_sec;
            b_usec = mypk.ts.tv_usec;
        }
        c_sec = (unsigned)mypk.ts.tv_sec - b_sec;
        c_usec = (unsigned)mypk.ts.tv_usec - b_usec;
        while(c_usec < 0) {
            c_usec += 1000000;
            c_sec--;
        }
        
        printf("Packet %d\n", curpkt);
        printf("%05u.%06u\n",(unsigned)c_sec,(unsigned)c_usec);
        printf("Captured Packet Length = %d\nActual Packet Length = %d\n\n",
                mypk.caplen, mypk.len);

        curpkt++;

        read(fd,buf,mypk.caplen);
}
    close(fd);
    exit(0);
}
