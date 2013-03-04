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

int main(int argc, const char * argv[])
{    
    if (!fork()) {
        char **argv1 = (char **)malloc(argc*sizeof(char *));
        
        argv1[0] = (char *)malloc(sizeof(argv1[1]));
        strcpy(argv1[0], argv[1]);
        argv1[1] = NULL;
        
        (void)signal(SIGHUP, SIG_IGN);
        
        execve(argv1[0], argv1, NULL);
        
        
        free(argv1[0]);
        free(argv1);
    }
    return 0;
}

