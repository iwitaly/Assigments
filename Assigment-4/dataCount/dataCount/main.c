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

int ppe[2];
pid_t pid;
int time = 2;
double size = 0;

void handler(int npid) {
    
    kill(pid, SIGKILL); //kill child
    
    char str[40];
    sprintf(str, "%lf Mb\n%lf Mb/sec", size, size/(time));

    write(STDOUT_FILENO, str, strlen(str));
}

int main(int argc, const char * argv[])
{
    pipe(ppe);
    
    pid = fork();
    
    if (pid == -1) {
        write(STDOUT_FILENO, "shit happends", strlen("shit happends"));
    }
    if (pid == 0) {
        //child
        close(ppe[0]);
        
        int sizeToWrite = 100000;
        char trash[sizeToWrite];//0.1 Mb
        
        while (1) {
            write(ppe[1], trash, sizeToWrite);
        }
    }
    else {
        //parent
        alarm(time);
        
        close(ppe[1]);
        
        struct sigaction action;
        action.sa_handler = handler;
        
        sigaction(SIGALRM, &action, NULL);
        
        int bufferSize = 100000;
        char buff[bufferSize]; //0.1 Mb
        
        while (1) {
            if (read(ppe[0], buff, bufferSize) != 0) {
                size += 0.1;
            }
            else {
                break;
            }
        }
    }
    
    return 0;
     
}

