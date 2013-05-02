#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

#define port 5000
#define numberOfConnections 2

char *inverseString(char *string) {
    int i;
    int n = (int)strlen(string);
    
    char *newString = (char *)malloc(n);
    
    for (i = n-1; i > -1; --i) {
        newString[n-i-1] = string[i];
    }
    
    return newString;
}

int main()
{
	int listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenFd < 0) {
		perror("");
		
		return -1;
	}
	
	struct sockaddr_in socketAddres;
	
	memset(&socketAddres, 0, sizeof(struct sockaddr_in));
	
	struct in_addr adrInInt;
	adrInInt.s_addr = INADDR_ANY;
	
	socketAddres.sin_family = AF_INET;
	socketAddres.sin_port = htons(port);
	socketAddres.sin_addr = adrInInt;
	
	int bindCheck = bind(listenFd, (struct sockaddr *)&socketAddres, sizeof(struct sockaddr_in));
	if (bindCheck < 0) {
		perror("");
		
		return -1;
	}
	
	int listenCheck = listen(listenFd, numberOfConnections);
	if (listenCheck < 0) {
		perror("");
		
		return -1;
	}
	
	printf("ready to work!\n");
	int sockFd = accept(listenFd, NULL, 0);	
	
	while (1) {
		if (sockFd != -1) {
			char buff[50];
			
			int numBytesRead = read(sockFd, buff, 20);
			
			buff[numBytesRead] = '\0';
			
			char *inverseStr = inverseString(buff);
			write(sockFd, inverseStr, 20);
			
			free(inverseStr);
			printf("%s\n%s", buff, inverseStr);
		}
		
		sleep(1);
	}
	
	close(sockFd);

	return 0;
}