//
//  main.c
//  dataCount
//
//  Created by Виталий Давыдов on 17.03.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int *adr;

void handler(int npid) {
    
    write(STDOUT_FILENO, "WOW!\n", 5);
    
    int check[1000000];
    read(adr[0], check, 10000);
    
    
    char str[5];
    sprintf(str, "%ld", sizeof(*check));
    write(STDOUT_FILENO, str, strlen(str));
}

int main(int argc, const char * argv[])
{
    int *ppe = (int *)malloc(sizeof(100e6));
    int ind = pipe(ppe);
    adr = ppe;
    
    
    pid_t pid = fork();
    
    if (pid == -1) {
        write(STDOUT_FILENO, "shit happends", strlen("shit happends"));
    }
    if (!fork()) {
        //child
        while (1) {
            int *trash = malloc(sizeof(int)*1e3);
            write(ppe[1], trash, sizeof(int)*1e3);
        }
    }
    else {
        //parent
        alarm(2);
        
        struct sigaction action;
        action.sa_handler = handler;
        
        sigaction(SIGALRM, &action, NULL);
        
        int status;
        wait(&status);
    }
    
    return 0;
     
}

