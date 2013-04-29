//
//  main.c
//  client
//
//  Created by Виталий Давыдов on 21.04.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

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
#define message "Hello, word!"

int main(int argc, const char * argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printf("socker error\n");
        
        return -1;
    }
    
    struct sockaddr_in socketAddres;
    socketAddres.sin_family = AF_INET;
    inet_aton(addr, &socketAddres.sin_addr);
    socketAddres.sin_port = port;
    
    int connectionResult = connect(fd, (struct sockaddr *)&socketAddres, sizeof(struct sockaddr_in));
    if (connectionResult < 0) {
        printf("connection error\n");
        
        return -1;
    }
    
    printf("ok connected!\n");
    
    size_t writtenSize = write(fd, message, strlen(message));
    
    if (writtenSize == strlen(message)) {
        printf("ok\n");
    }
    
    close(fd);
    
    return 0;
}

