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
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sockerAddres;
	
	memset(&sockerAddres, 0, sizeof(struct sockaddr_in));
	
	struct in_addr adrInInt;
	adrInInt.s_addr = INADDR_ANY;
	
	sockerAddres.sin_family = AF_INET;
	sockerAddres.sin_port = htons(port);
	sockerAddres.sin_addr = adrInInt;
	
	bind(fd, (struct sockaddr *)&sockerAddres, sizeof(struct sockaddr_in));
	
	listen(fd, numberOfConnections);
		
	while (1) {
		int sockFd = accept(fd, NULL, 0);		
		
		if (sockFd != -1) {
			printf("connected!");

			char buff[20];
			
			int numBytesRead = read(sockFd, buff, 20);
			buff[numBytesRead] = '\0';
			
			printf("%s\n", buff);
			
			close(sockFd);
		}
	}
	
	return 0;
}