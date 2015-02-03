#include <sys/types.h>	
#include <stdio.h>		
#include <stdlib.h>		
#include <string.h>		
#include <unistd.h>		
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <netbas/netbas.h>
#include <sys/ioctl.h>
#include <netdb.h>



#define SENDLEN 40
int sockfd;
struct sockaddr_in dest;
void sendrequest();
void ping();

int sigact(int signo, void (*handler)(int))
{
        struct sigaction sa;
                                                                                           
        sa.sa_handler = handler;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);
        return sigaction(signo, &sa, NULL);
}

volatile int timeout;
void sigalarm(int signo)
{
	char str[] = "sigalarm hld call\n";
	write(1,str,sizeof(str));
	timeout = 1;
}

void mysleep()
{
	sigact(SIGALRM, sigalarm);
	//printf("alarm call at user\n");
	alarm(1);
	timeout = 0;
	while (timeout == 0){
		//printf("prog run...\n");
	}
}

//#define main ping_main
int main(int argc,char **argv)
{
	struct hostent *host;
	/*char* p;

	printf("malloc at 0x%x\n",malloc(1022));
	printf("malloc at 0x%x\n",malloc(1022));
	p=malloc(4096);
	printf("malloc 4096 at 0x%x\n",p);
	free(p);
	printf("malloc at 0x%x\n",malloc(1022));
	printf("malloc at 0x%x\n",malloc(1022));
	*/
	if(argc < 2) {
                fprintf(stderr, "usage(%d): ping address\n", argc);
                return 1;
    }



	host = gethostbyname(argv[1]);
	if(host == NULL)
	{
		printf("can't get IP address of host '%s'\n", argv[1]);
		return 1;
	}


	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;

	//inet_aton( argv[1], &dest.sin_addr);
	memcpy(&dest.sin_addr, host->h_addr, host->h_length);

	/* sock start up */
	if((sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP)) <0){
		printf("socket");
		return 1;
	}

	printf("PING %s : Send %d data bytes.\n", inet_ntoa(dest.sin_addr), SENDLEN);

	ping();
	return 0;
}

unsigned short in_cksum(unsigned short *addr, int nleft)
{
        int sum = 0;
        unsigned short *w = addr;
        unsigned short answer = 0;
                                                                                
       while (nleft > 1)  {
                sum += *w++;
                nleft -= 2;
        }
        if (nleft == 1) {
                *(unsigned char *)(&answer) = *(unsigned char *)w;
                sum += answer;
        }
        sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
        sum += (sum >> 16);                     /* add carry */
        answer = ~sum;                          /* truncate to 16 bits */
	return answer;
}

//static struct timeval _tv;
void sendrequest()
{
	int i;
	static int nsent = 0;
    char sendbuf[1500];
	struct icmphdr *ich;
	struct timeval *tv;

	memset(sendbuf,0,sizeof(sendbuf));
	
	ich = (struct icmp *)sendbuf;
	ich->type = ICMP_ECHO;
	ich->code = 0;
	ich->un.echo.id = getpid();
	ich->un.echo.sequence = nsent++;
	tv = (struct timeval *)&sendbuf[8];
	gettimeofday(tv, 0);
	ich->checksum = 0;
	ich->checksum = in_cksum((unsigned short *)ich, SENDLEN);
	
	sendto(sockfd, sendbuf, SENDLEN, 0, (struct sockaddr*)&dest, sizeof(dest));

}

double computertt(struct timeval * s, struct timeval * r)
{
        struct timeval t;
        if (r->tv_usec < s->tv_usec) {
                r->tv_sec--;
                r->tv_usec += 1000000;
        }
        t.tv_usec = r->tv_usec - s->tv_usec;
        t.tv_sec = r->tv_sec - s->tv_sec;
	return t.tv_sec*1000.0 + t.tv_usec/1000.0;
}

void dump_buf(char *label, void *data, int length)
{
	int i, j;
	int *intptr = data;
	char *charptr = data;
	char buf[10], line[80];

	printf("%s: dump of %d bytes of data at 0x%p\n\n", 
		label, length, data);
	for (i = 0; i < length; i += 16) {
		line[0] = 0;
		for (j = 0; (j < 4) && (i + j * 4 < length); j++) {
			sprintf(buf, " %08x", intptr[i / 4 + j]);
			strcat(line, buf);
		}
		buf[0] = ' ';
		buf[2] = 0;
		for (j = 0; (j < 16) && (i + j < length); j++) {
			buf[1] = isprint(charptr[i + j]) ? charptr[i + j] : '.';
			strcat(line, buf);
		}
		printf("%s\n", line);
	}
}

struct iphdr1 
{ 
  unsigned short h_len_and_vers; // Length of the header and IP version
  unsigned short total_len;      // Total length of the packet 
  unsigned short ident;          // Unique identifier 
  unsigned short frag_and_flags; // Flags 
  unsigned char  ttl;
  unsigned char proto;           // Protocol (TCP, UDP etc) 
  unsigned short checksum;       // IP checksum 
   
  unsigned int source_ip;        // Source IP address
  unsigned int dest_ip;          // Destination IP address
};


int recvreply(unsigned char * recvbuf, int recvbuflen, 
	struct sockaddr_in  *their_adr)
{
	//struct ip *ih = (struct ip *) recvbuf;
	int ihlen = 0;//ih->ip_hl << 2;
  struct iphdr1 *iphdr; 
  iphdr = (struct iphdr1 *) recvbuf;
  ihlen = (iphdr->h_len_and_vers & 0x0F) * 4;

	struct icmphdr *ich = (struct icmp *)(recvbuf + ihlen); 
	char rttstr[16];

	int i;

	printf("proto = %d, source_ip=%x\n", iphdr->proto,iphdr->source_ip);
	
	if (ich->type != ICMP_ECHOREPLY && ich->type != ICMP_ECHO){
		dump_buf("ICMP", recvbuf,recvbuflen);
		printf("recv error %x with %d bytes\n", ich->type,recvbuflen);
        return 0;
	}
	if (ich->un.echo.id != getpid())
		return 0;
	struct timeval *tsend = (struct timeval *)&recvbuf[8];
	struct timeval trecv;
	gettimeofday(&trecv, 0);
        double rtt = computertt(tsend, &trecv);
	if (rtt < 1)
		strcpy(rttstr, "<1");
	else
		sprintf(rttstr, "%.2f", rtt);

	printf("%d bytes from %s: seq = %u, rtt = %s ms\n",
		recvbuflen, inet_ntoa(their_adr->sin_addr),
		ich->un.echo.sequence,  rttstr);

/*	printf("Reply from %s: bytes=%d seq=%d time=%dms TTL=%d\n",
		inet_ntoa(ih->ip_src),icmplen,
		ich->un.echo.sequence,rttstr, ih->ip_ttl);*/
        return 1;
}

void ping()
{
	int i;
    unsigned char recvbuf[1500];
	int nrecv;
	unsigned f =1;
	int n = 0;
	struct sockaddr their_adr;
	int adr_len=sizeof(struct sockaddr);
	fd_set read_handles;
	struct timeval timeout;
	int selectval;

	ioctl(sockfd, FIONBIO, &f);
	
	for(i=0;;i++) {

		sendrequest();

		#if 1		
		//thread_msleep(1000);
		//#else
		FD_ZERO(&read_handles);
		//FD_SET(_devfd(sockfd), &read_handles);
		FD_SET((sockfd), &read_handles);
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		selectval = select((sockfd) + 1,
			&read_handles, NULL, NULL, &timeout);
		if(selectval < 0)
		{
			printf("select(c_sock) failed; err=%d\n",
				errno);
			break;
		}
		else if(selectval==0){
			printf("Destination host unreachable.\n");
			continue;
		}
		else{
		}
		#endif

		memset(&their_adr,0,sizeof(their_adr));
		adr_len=sizeof(struct sockaddr);

        //do {
			memset(recvbuf,0,sizeof(recvbuf));
		nrecv = recvfrom(sockfd, recvbuf,
			sizeof(recvbuf),0, &their_adr, &adr_len);
		if (nrecv < 0){
				printf("Destination host unreachable.\n");
				break ;
		}
			n++;

			printf("data from %d with %d bytes\n", adr_len, nrecv);

		if(!recvreply(recvbuf, nrecv, (struct sockaddr_in  *)&their_adr))
			break;

		//mysleep();
		
	}

	printf("Ping statistics for %s:\n"
		"Packets: Sent = %d, Received = %d, Lost = %d (0%% loss),\n"
		"Approximate round trip times in milli-seconds:\n"
		"Minimum = %dms, Maximum = %dms, Average = %dms\n",
		inet_ntoa(dest.sin_addr),i,n,i-n,
		0,0,12);

}
