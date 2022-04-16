#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>

#define server_ip "127.0.0.1"

int main() {
	int fd;
	char buf[200];
	struct sockaddr_in servaddr;
	fd = socket(AF_INET,SOCK_DGRAM,0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	inet_pton(AF_INET, server_ip,&servaddr.sin_addr);
	printf("Connection with Server Established\n");
	fgets(buf,20,stdin);
	socklen_t addr_len;
	addr_len = sizeof(struct sockaddr_in);
	sendto(fd,buf,strlen(buf),0,(struct sockaddr *)&servaddr,addr_len);
	printf("Data Recieved by server: %s\n",buf);
	recvfrom(fd,buf, 10000,0, (struct sockaddr *)&servaddr,&addr_len);
	printf("Data is Toggled and received by the Server: %s\n",buf);
	close(fd);
	return 0;
}

