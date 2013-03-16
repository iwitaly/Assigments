//
//  main.c
//  cpulimit
//
//  Created by Виталий Давыдов on 10.03.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define TIME_TO_CHECK 10

pid_t pid;

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

int main(int argc, const char * argv[])
{
//    if (argc < 3) {
//        printf("wrong input\n");
//        
//        return -1;
//    }
    
    int cpuLimit = 5; //atoi(argv[1]);
    const char *program = "/Users/iwitaly/Documents/Assigments/Assigment-3/cpulimit/cpulimit/test"; //argv[2];
    
    if (cpuLimit == 0) {
        printf("wrong input\n");
        
        return -1;
    }
    else {
        cpuLimit /= 100.0;
    }
    
    pid = fork();
    
    if (pid == -1) {
        write(STDOUT_FILENO, "oh, wrong\n", 10);
        
        return -1;
    }
    
    if (pid == 0) {
        //child
        execve(program,  NULL/*makeArguments(argv, argc)*/, NULL);
        
        write(STDOUT_FILENO, "shit happends\n", strlen("shit happends\n"));
    }
    else {
        //parent, delegate child
        float prevTimeWork = 0;
        float totalTimeWork = TIME_TO_CHECK;
        
        while (1) {
            if (kill(pid, 0) == -1) {
                write(STDOUT_FILENO, "programm has finished\n", strlen("programm has finished\n"));
                
                break;
            }
            else {
                float persent = 0;
                
                while (persent < cpuLimit) {
                    prevTimeWork += TIME_TO_CHECK;
                    totalTimeWork += TIME_TO_CHECK;
                    persent = prevTimeWork/totalTimeWork;
                }
                kill(pid, SIGSTOP);
                usleep(TIME_TO_CHECK);
                kill(pid, SIGCONT);
            }
            
            prevTimeWork = 0;
        }
    }
    
    return 0;
}

