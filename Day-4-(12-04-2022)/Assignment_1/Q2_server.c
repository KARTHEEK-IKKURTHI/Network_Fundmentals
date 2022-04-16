#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>

void press(int);

int main(){
	int fd,confd,return_val;
	socklen_t client;
	struct sockaddr_in cliaddr, servaddr;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr,0,sizeof(servaddr));	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000);
	return_val = bind(fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Welcome to My World\n");
	listen(fd, 5);
	while(1) {
		char k[50];
		pid_t d;
		int n;
		client= sizeof(cliaddr);
		confd = accept(fd, (struct sockaddr *) &cliaddr, &client);
		printf("\nClient connected\n");
		d = fork();
		if(d == 0) {
			close(fd);
			press(confd);
		}
		close(confd);
	}
	return 0;
}

void press(int q){
	int a;
	char kar[40];
	a = read(q, kar, 40);
	kar[a]='\0';
	printf("Blueprint received from client: %s", kar);
	printf("Server %d is currently handling the client request\n",getpid());
	write(q, "Thank you for connecting to My World\n",43);
	exit(0);
}
