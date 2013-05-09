//
//  main.c
//  shared memory
//
//  Created by Виталий Давыдов on 09.05.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define sharedMemoryName "yoMemory"
#define bufferSize 64000


int main(int argc, const char * argv[])
{
    //create shared memory for to proces than test
    
    int fd1 = shm_open(sharedMemoryName, O_CREAT | O_RDWR, 0400);
    if (fd1 < 0) {
        perror("");
        
        return -1;
    }
    
    int truncateResult = ftruncate(fd1, bufferSize);
    if (truncateResult < 0) {
        perror("");
        
        return -1;
    }
    
    int *buffer = (int *)mmap(NULL, bufferSize, PROT_READ | PROT_WRITE, MAP_SHARED  ,fd1 , 0);
    if (buffer == MAP_FAILED) {
        perror("");
        
        return -1;
    }
    
    
    return 0;
}

