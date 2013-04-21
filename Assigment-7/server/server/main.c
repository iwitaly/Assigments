//
//  main.c
//  server
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
    
    struct sockaddr_in sockerAddres;
    
    inet_aton(addr, &sockerAddres.sin_addr);
    
    sockerAddres.sin_family = AF_INET;
    sockerAddres.sin_port = htons(port);
//    sockerAddres.sin_addr.s_addr = inet_addr(addr);
    
    connect(fd, (struct sockaddr *)&sockerAddres, sizeof(struct sockaddr_in));
    
    if (fd == -1) {
        printf("shit\n");
    }
    
    
//    char buff[10];//correct
    
    write(fd, message, strlen(message));
    
//    sleep(0.5);
    
//    read(fd, buff, 10);
    
    close(fd);
    
//    printf("ke");
    
    return 0;
}

