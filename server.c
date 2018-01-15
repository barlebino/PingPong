#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>


void error(char *msg){
	perror(msg);
	exit(0);
}


int main(int argc,char *argv[]){
	int sock,sock2,length,length2,fromlen,fromlen2,n,n2;
	struct sockaddr_in server,server2;
	struct sockaddr_in from,from2;
	char buf[1024];
	char buf2[1024];


	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		error("error occured while opening socket.\n");
	}
	sock2=socket(AF_INET,SOCK_DGRAM,0);
	if(sock2<0){
		error("error occured while opening socket2.\n");
	}

	length=sizeof(server);
	bzero(&server,length);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi("1337"));

	length2=sizeof(server2);
	bzero(&server2,length2);
	server2.sin_family=AF_INET;
	server2.sin_addr.s_addr=INADDR_ANY;
	server2.sin_port=htons(atoi("1338"));

	if(bind(sock,(struct sockaddr *)&server,length)<0){
		error("error occured while binding socket.\n");
	}


	if(bind(sock2,(struct sockaddr *)&server2,length2)<0){
		error("error occured while binding socket2.\n");
	}

	fromlen=sizeof(struct sockaddr_in);

	fromlen2=sizeof(struct sockaddr_in);

	while(1){
		n=recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
		n2=recvfrom(sock2,buf2,1024,0,(struct sockaddr *)&from2,&fromlen);
		if(n<0){
			error("recvfrom");
		}	
		if(n2<0){
			error("recvfrom2");
		}	

		write(1,"recieved a datagram:",21);
		write(1,buf,n);
		write(1,"recieved a datagram from 2:",27);
		write(1,buf2,n2);		
		n=sendto(sock,buf2,17,0,(struct sockaddr *)&from,fromlen);
		n2=sendto(sock2,buf,17,0,(struct sockaddr *)&from2,fromlen2);

		if(n<0 ){
			error("error occured while sending.\n");
		}
		if(n2<0 ){
			error("error occured while sending2.\n");
		}



	}

return 0;
}