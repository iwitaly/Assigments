//
//  main.c
//  client
//
//  Created by Виталий Давыдов on 21.04.13.
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

#define addr "192.168.200.9"
#define port 5000
#define message "Hello, word!"

int main(int argc, const char * argv[])
{
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
    
    while (1) {
        char mes[50];
        gets(mes);
        
        write(fd, mes, strlen(mes));
        
        read(fd, mes, strlen(mes));
        
        printf("%s\n", mes);
    }
    
    close(fd);
    
    return 0;
}

