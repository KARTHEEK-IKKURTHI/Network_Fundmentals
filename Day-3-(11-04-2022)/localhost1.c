/* To get the detatls of the hosts .
Version: 1.0
Author: Team -c
*/
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
int main(int argc, char *argv[]){
	char hostname[HOST_NAME_MAX + 1];
	//bits/local_lim.h:#define HOST_NAME_MAX 64
	//bits/posixi_lim.h:#define _POSIX_HOST_NAME_MAX 255
	hostname[HOST_NAME_MAX] = 0;
	if (gethostname(hostname, HOST_NAME_MAX) == 0){
	puts(hostname);
	}
	else{
	perror("gethostname");
	}
return 0;
}

