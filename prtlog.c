#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include "dnet.h"
#include "pcap.h"
#include "prtlog.h"


int main(int argc, char* argv[]) {
    
    if(argc !=2){
        printf("Usage: prtlog network*.log\n");
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
    struct eth_hdr ehead;
    int hsize;
    struct arp_hdr arphead;
    struct ip_hdr iphead;

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
        printf("Captured Packet Length = %d\nActual Packet Length = %d\n",
                mypk.caplen, mypk.len);

        curpkt++;
        
        hsize = read(fd,&ehead,sizeof(ehead));
        
        if(ntohs(ehead.eth_type) == ETH_TYPE_IP) {
            printf("Ethernet Header\n   IP\n");
            hsize += read(fd, &iphead, sizeof(iphead));
            validateIp(&iphead);
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_ARP) {
            printf("Etherner Header\n   ARP\n");
            hsize += read(fd, &arphead,sizeof(arphead));
            validateArp(&arphead);
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_PUP) {
            printf("Ethernet Header\n   PUP\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_REVARP) {
            printf("Ethernet Header\n   REVARP\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_8021Q) {
           printf("Ethernet Header\n   8021Q\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_IPV6) {
             printf("Ethernet Header\n   IPV6\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_MPLS) {
             printf("Ethernet Header\n   MPLS\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_MPLS_MCAST) {
             printf("Ethernet Header\n   MPLS_MCAST\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_PPPOEDISC) {
             printf("Ethernet Header\n   PPPOEDISC\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_PPPOE) {
             printf("Ethernet Header\n   PPPOE\n");
        } else if(ntohs(ehead.eth_type) == ETH_TYPE_LOOPBACK) {
             printf("Ethernet Header\n   LOOPBACK\n");
        } else {
            printf("Ethernet Header\n   UNRECOGNIZED\n");
        }
     
        printf("\n");
        readRest(fd,buf,(mypk.caplen-hsize));
}
    close(fd);
    exit(0);
}

int readRest(int fd, char *buff[], int readin) {
    return read(fd, buff, readin);
}

void validateArp(struct arp_hdr *ah) {
     if(ntohs(ah->ar_op) == ARP_OP_REQUEST) {
         printf("   arp operation = Arp Request\n");
     } else if(ntohs(ah->ar_op) == ARP_OP_REPLY) {
         printf("   arp operation = Arp Reply\n");
     } else if(ntohs(ah->ar_op) == ARP_OP_REVREQUEST) {
         printf("   arp operatiom = Arp Rev Request\n");
     } else if(ntohs(ah->ar_op) == ARP_OP_REVREPLY) {
         printf("   arp operation = Arv Rev Reply\n");
     } else {
         printf("   UNRECOGNIZED\n");
     }
}

void validateIp(struct ip_hdr *ih) {
     if(ih->ip_p ==IP_PROTO_ICMP) {
            printf("    ICMP\n");
     } else if(ih->ip_p == IP_PROTO_IGMP) {
            printf("    IGMP\n");
     } else if(ih->ip_p == IP_PROTO_TCP) {
            printf("    TCP\n");
     } else if(ih->ip_p == IP_PROTO_UDP) {
            printf("    UDP\n");
     } else {
            printf("    UNRECOGNIZED\n");
     }
}

