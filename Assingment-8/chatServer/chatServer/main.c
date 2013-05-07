//
//  main.c
//  chatServer
//
//  Created by Виталий Давыдов on 06.05.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define port 5000
#define numberOfConnections 30
#define maxNumberOfUsersInTheChat 30
#define maxChatSize 50000
#define maxMessageLength 140

int main(int argc, const char * argv[])
{
    //initialisation connection
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
	
	printf("server is ready to work\n");
    
    //now initialise logic and server contolling
    fd_set readSet, bufferReadSet, writeSet, bufferWriteSet;
    FD_ZERO(&readSet);
    FD_ZERO(&writeSet);

    FD_SET(listenFd, &readSet);
    bufferReadSet = readSet;
    
    int maxSocket = listenFd + 1;
    int currentNumberOfUsers = 0;
    int usersSockets[maxNumberOfUsersInTheChat];
    
    char chat[maxChatSize]; //implement history
    
    char usersMessage[maxMessageLength];
    
    while (1) {
        //get new users by checking listenFd
        
        if (FD_ISSET(listenFd, &bufferReadSet) != 0) {
            usersSockets[currentNumberOfUsers] = accept(listenFd, NULL, 0);
            
            printf("user connected %d\n number of users %d\n", usersSockets[currentNumberOfUsers], currentNumberOfUsers);
            
            if (usersSockets[currentNumberOfUsers] != -1) {
                //add user
                FD_SET(usersSockets[currentNumberOfUsers], &writeSet);
                FD_SET(usersSockets[currentNumberOfUsers], &readSet);
                
                if (usersSockets[currentNumberOfUsers] + 1 > maxSocket) {
                    maxSocket = usersSockets[currentNumberOfUsers];
                }
                
                ++currentNumberOfUsers;
            }
        }
        
        
        if (currentNumberOfUsers > 0) {
            bufferReadSet = readSet;
            bufferWriteSet = writeSet;
            
            select(maxSocket, &bufferReadSet, &bufferWriteSet, NULL, NULL);
            
            //chating control
            
            int i = 0;
            for (; i < currentNumberOfUsers; ++i) {
                if (FD_ISSET(usersSockets[currentNumberOfUsers], &bufferWriteSet) != 0) {
                    //ok, now read\write
                    
                    printf("write\read!\n");
                    
                    int readSize = (int)read(usersSockets[currentNumberOfUsers], usersMessage, maxMessageLength-2);
                    
                    if (readSize < 0) {
                        perror("");
                        
                        exit(-1);
                    }
                    
                    printf("%s\n", usersMessage);

                    usersMessage[readSize] = '\n';
                    usersMessage[readSize+1] = '\0';
                    
                    //send message to all men
                    
                    int j = 0;
                    
                    for (; j < currentNumberOfUsers; ++j) {
                        if (FD_ISSET(usersSockets[j], &bufferWriteSet) > 0) {
                            int writtenSize = (int)write(usersSockets[j], usersMessage, readSize);
                            
                            if (writtenSize < 0) {
                                perror("");
                                
                                exit(-1);
                            }
                        }
                    }
                }
            }
        }

    }
    
    return 0;
}

