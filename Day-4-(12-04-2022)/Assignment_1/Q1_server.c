#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

int main() {
	int p,return_val,q;
	socklen_t client;
	struct sockaddr_in cliaddr, servaddr;
	char kar[10000];
	p = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000);
	return_val = bind(p, (struct sockaddr *) &servaddr, sizeof(servaddr));
	client = sizeof(struct sockaddr_in);
	while(1){
		q=recvfrom(p,kar,10000,0, (struct sockaddr *)&cliaddr,&client);
		kar[q]='\0';
		printf("Data received from client: %s\n",kar);
		for(int i=0; i<strlen(kar); i++) {
			if((kar[i] >= 'a' ) && (kar[i] <= 'z')) {
				kar[i] -= 0x20;
			}
			else if((kar[i] >= 'A' ) && (kar[i] <= 'Z')) {
				kar[i] += 0x20;
			}
		}
		sendto(p,kar,strlen(kar),0,(struct sockaddr *)&cliaddr,client);	
	}
	return 0;
}


