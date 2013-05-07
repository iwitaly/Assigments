//
//  main.c
//  chatClient
//
//  Created by Виталий Давыдов on 06.05.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define addr "127.0.0.1"
#define port 5000
#define maxMessageLength 140
#define maxChatSize 50000

int main(int argc, const char * argv[])
{
    //opening socket fd and making connection
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("");
        
        return -1;
    }
    
    struct sockaddr_in socketAddres;
    socketAddres.sin_family = AF_INET;
    inet_aton(addr, &socketAddres.sin_addr);
    socketAddres.sin_port = htons(port);
    
    int connectionResult = connect(fd, (struct sockaddr *)&socketAddres, sizeof(struct sockaddr_in));
    if (connectionResult < 0) {
        perror("");
        
        return -1;
    }
    
    printf("ok connected!\nenter the string\n");
    
    //now making client logic
    
    fd_set writeSet, readSet;
    FD_ZERO(&writeSet);
    FD_ZERO(&readSet);
    FD_SET(fd, &writeSet);
    FD_SET(fd, &readSet);
    
    char message[maxMessageLength] = "hello, chat";
    char chat[maxChatSize];
    
    while (1) {
        printf("%s\n", message);
        write(fd, message, strlen(message));
        sleep(10);
    }
    
//    while (1) {
//        int numberOfWorkingDescriptiors = select(fd + 1, &writeSet, &readSet, NULL, NULL);
//        
//        if (numberOfWorkingDescriptiors < 2) {
//            if (errno != EINTR) {
//                printf("something wrong with descriptors\n");
//                
//                exit(-1);
//            }
//        }
//        
//        int dataRead = (int)read(fd, chat, maxChatSize);
//        chat[dataRead] = '\n';
//        chat[dataRead+1] = '\0';
//        
//        gets(message);
//        
//        int dataWritten = (int)write(fd, message, strlen(message));
//        
//    }
    return 0;
}

