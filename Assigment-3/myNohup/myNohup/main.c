//
//  main.c
//  myNohup
//
//  Created by Виталий Давыдов on 02.03.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

pid_t pid;

char **makeArguments(const char **argv, int argc) {
    char **argv1 = (char **)malloc(argc*sizeof(char *));
    
    argv1[0] = (char *)malloc(sizeof(argv1[1]));
    strcpy(argv1[0], argv[1]);
    argv1[1] = NULL;
    
    return argv1;
}

int main(int argc, const char * argv[])
{
    if (argc < 2) {
        write(STDOUT_FILENO, "wrong input\n", sizeof("wrong input\n"));
        
        return -1;
    }
    
    pid = fork();

    if (pid == -1) {
        write(STDOUT_FILENO, "oh, wrong\n", 10);
        
        return -1;
    }
    if (pid == 0) {
        execve(argv[1], makeArguments(argv, argc), NULL);
    }
    else {
        static struct sigaction act;
        act.sa_handler = SIG_IGN;
        
        sigaction(SIGHUP, &act, NULL);
    }
    return 0;
}