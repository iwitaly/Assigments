//
//  main.c
//  timeLimit
//
//  Created by Виталий Давыдов on 04.03.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

pid_t pid;

void handler(int npid) {
    write(STDOUT_FILENO, "out of terminate!", strlen("out of terminate!"));
    
    kill(pid, SIGKILL);
}


char **makeArguments(const char **argv, int argc) {
    char **newArgv = (char **)malloc((argc-1)*sizeof(char *));
    int i;
    
    for (i = 2; i < argc; ++i) {
        newArgv[i-2] = (char *)malloc(sizeof(argv[i]));
        strcpy(newArgv[i-2], argv[i]);
    }
    
    newArgv[argc-1] = NULL;
    
    return newArgv;
}

int main(int argc, const char * argv[]) {
    if (argc < 3) {
        printf("wrong input\n");
        return -1;
    }

    int timeLimit = atoi(argv[1]);
    const char *program = argv[2];
    
    if (timeLimit <= 0) {
        printf("wrong input\n");
        return -1;
    }
    
    pid = fork();
        
    alarm(timeLimit);
    
    if (pid == -1) {
        write(STDOUT_FILENO, "oh, wrong\n", 10);
        
        return -1;
    }
    if (pid == 0) {
        //child
        execve(program, makeArguments(argv, argc), NULL);
        
        write(STDOUT_FILENO, "oh, smth goes wrong!", strlen("oh, smth goes wrong!"));
    }
    else {
        //parent        
        struct sigaction act;
        act.sa_handler = handler;
        
        if (sigaction(SIGALRM, &act, NULL) != 0) {
            write(STDOUT_FILENO, "shit\n", 5);
        }
        
        int status;
        
        wait(&status);
    }
    
    return 0;
}