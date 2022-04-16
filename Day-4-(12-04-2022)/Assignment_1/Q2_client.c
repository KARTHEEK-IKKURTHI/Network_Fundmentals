#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>

int main() {
	char *serv_ip = "127.0.0.1";
	int fd, res;
	char k[50];
	int p = 0;
	struct sockaddr_in servaddr;
	fd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	inet_pton(AF_INET, serv_ip,&servaddr.sin_addr);
	res = connect(fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Established connection with server\n");
	fgets(k, 50, stdin);
	write(fd,k,strlen(k));
	p = read(fd,k, 50);
	k[p] = '\0';
	socklen_t addr_len;
	addr_len = sizeof(struct sockaddr_in);
	res = sendto(fd,k,strlen(k),0,(struct sockaddr *)&servaddr,addr_len);
	printf("Data received from server: %s\n",k);
	close(fd);
	return 0;
}

