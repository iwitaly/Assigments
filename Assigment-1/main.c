//
//  main.c
//  workWithDescriptors
//
//  Created by Виталий Давыдов on 15.02.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//сделать цикл, закрыть файл, сделать нормальное взаимодействие read\write сохранить число байт, прочтенное


void generateTextFilesInAmount(int n) {
    int x[n];
    char *name1 = "/Users/iwitaly/Documents/физтех/Семестр 4/АКОС/workWithDescriptors/workWithDescriptors/fileN.txt";
    char *name = (char *)malloc(strlen(name1)*sizeof(char));
    name = strcpy(name, name1);
    int len = (int)strlen(name1);
    
    int i;
    for (i = 0; i < n; ++i) {
        name[len-5] = (char)((int)'0'+i);
        printf("%s\n", name);
        x[i] = open(name, O_RDWR | O_CREAT, 0400);
    }
    
    for (i = 0; i < n; ++i) {
        if (x[i] >= 0) {
            char c = (char)((int)'0'+i);
            write(x[i], &c, 1);
        }
    }
}

int main(int argc, char * argv[])
{
    int i;
    
   for (i = 1; i < argc; ++i) {
       int fildes = open(argv[i], O_RDONLY);
       
       if (fildes < 0) {
           printf("file not found");
		   break;
       }
       else {
	//copy in buffer
           while (1) {
               int sizeOfString = 1024;
               char *string = (char *)malloc(sizeOfString*sizeof(char));
               int len = 0;
               
               len = read(fildes, string, sizeOfString);
               
               if (len == 0) {
                   break;
               }
               else {
                   write(STDOUT_FILENO, string, len);
                   write(STDOUT_FILENO, "\n", 1);
                   
                   free(string);
               }
           }
       }
       
       close(fildes);
   }
    
    return 0;
}

