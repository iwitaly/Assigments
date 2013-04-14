//
//  main.c
//  semaphores
//
//  Created by Виталий Давыдов on 09.04.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>

pid_t pid;

int main(int argc, const char * argv[])
{
    int numberOrIncrementation = 5;
    
    int fd = open("/Users/iwitaly/Documents/Assigments/Assigment-5/semaphores/semaphores/test.txt", O_RDWR | O_CREAT, 0400);
    
    if (fd < 0) {
        write(STDOUT_FILENO, "problem with opening", strlen("problem with opening"));
        
        exit(-1);
    }
    
    sem_t *sem = sem_open("/sem1", O_RDWR | O_CREAT, 0666, 1);
    
    if (sem == SEM_FAILED) {
        write(STDOUT_FILENO, "problem with creating semaphor", strlen("problem with creating semaphor"));
        
        exit(-1);
    }
    
    pid = fork();
    
    if (pid == -1) {
        write(STDOUT_FILENO, "problem with fork()", strlen("problem with fork()"));
        
        exit(-1);
    }
    
    int i;
    
    for (i = 0; i < numberOrIncrementation; ++i) {
        if (sem_wait(sem) < 0) {
            write(STDOUT_FILENO, "problem with semaphore", strlen("problem with semaphore"));
            
            exit(-1);
        }
        
        char number[9];
        
        lseek(fd, 0, SEEK_SET);
        
        int byteReadedFromFile = (int)read(fd, number, 9);
        
        if (byteReadedFromFile < 0) {
            write(STDOUT_FILENO, "problem with read from file", strlen("problem with read from file"));
            
            exit(-1);
        }
        
        lseek(fd, 0, SEEK_SET);
        
        number[byteReadedFromFile] = '\0';
        
        write(STDOUT_FILENO, number, 4);
        
        int numberReadFromFile = atoi(number);
        ++numberReadFromFile;
        
        sprintf(number, "%d", numberReadFromFile);
        
        printf("%s", number);
        
        write(STDOUT_FILENO, number, byteReadedFromFile);
        
        if (write(fd, number, byteReadedFromFile) < 0) {
            write(STDOUT_FILENO, "problem with write from file", strlen("problem with read from file"));
            
            exit(-1);
        }
        
        sem_post(sem);
    }
    
    return 0;
}