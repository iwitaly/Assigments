#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define addr "10.0.0.7"
#define port 5000
#define numberOfConnections 2

int main()
{
	int listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenFd < 0) {
		printf("socker error\n");
		
		return -1;
	}
	
	struct sockaddr_in socketAddres;
	
	memset(&socketAddres, 0, sizeof(struct sockaddr_in));
	
	struct in_addr adrInInt;
	adrInInt.s_addr = INADDR_ANY;
	
	socketAddres.sin_family = AF_INET;
	socketAddres.sin_port = port;
//	inet_aton(addr, &socketAddres.sin_addr);
	socketAddres.sin_addr = adrInInt;
	
	int bindCheck = bind(listenFd, (struct sockaddr *)&socketAddres, sizeof(struct sockaddr_in));
	if (bindCheck < 0) {
		printf("bind error\n");
		
		return -1;
	}
	
	int listenCheck = listen(listenFd, numberOfConnections);
	if (listenCheck < 0) {
		printf("listen error\n");
		
		return -1;
	}
	
	printf("all ok\n");
	
	while (1) {
		int sockFd = accept(listenFd, NULL, 0);			
		if (sockFd != -1) {
			printf("connected!");

			char buff[20];
			
			int numBytesRead = read(sockFd, buff, 20);
			buff[numBytesRead] = '\0';
			
			printf("%s\n", buff);
			
			close(sockFd);
		}
		
		sleep(1);
	}
	
	return 0;
}