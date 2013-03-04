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

void analize(int npid) {
    printf("shit happens");
}

int main(int argc, const char * argv[]) {
    if (argc < 3) {
        printf("wrong input\n");
        return 0;
    }
    
    int timeLimit = atoi(argv[1]);
    const char *program = argv[2];
    
    if (timeLimit == 0) {
        printf("wrong input\n");
        return 0;
    }
    
    (void)signal(SIGALRM, analize);
    int pid;
    if ((pid = fork()) == 0) {
        alarm(timeLimit);
        execve(program, NULL, NULL);        
    }
    
    return 0;
}