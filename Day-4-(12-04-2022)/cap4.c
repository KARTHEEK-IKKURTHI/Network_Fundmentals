

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>


main(){
	int pack_socket,n;
	struct sockaddr_ll sa;
	socklen_t sl;
	char buf[2000];
//Sock_raw keeps physical layer header, sock_dgram removes it.
	pack_socket = socket(PF_PACKET,SOCK_DGRAM,htons(ETH_P_ALL));
	if(pack_socket < 0){
		printf("Failed to open packet socket \n");
		exit(0);
		
	}
	
	printf("Packet Socket Succesfully Opened \n");
	
	while(1){	
		sl = sizeof(struct sockaddr_ll);
		n = recvfrom(pack_socket,buf,2000,0,(struct sockaddr *)&sa,&sl);
		printf("Recieved Packet of length %d\n",n);
		printf("Packet type =%d\n",sa.sll_pkttype);
		printf("Hardware Address length =%d\n",sa.sll_halen);
		printf("Protocol =%x\n",ntohs(sa.sll_protocol));
		//refer to netpacket/packet.h file for pkttype values.
		//refer linux/if_ether.h for list of protocol types.
		//0x800 is forip ,0x806 for ARP etc.
		}
		close(pack_socket);
}
