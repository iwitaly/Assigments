#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    int fd = open("/Users/iwitaly/Documents/Assigments/Assigment-5/semaphores/semaphores/test.txt", O_RDWR | O_CREAT, 0400);
    
    if (fd == -1) {
        write(STDOUT_FILENO, "error", strlen("error"));
    }
    
    int n = 200;
    
    int i = 0;
    
    for (i = 0; i < n; ++i) {
        write(fd, "1", 1);
    }
    
    return 0;
}