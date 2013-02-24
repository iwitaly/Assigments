//
//  main.c
//  myLsCommand
//
//  Created by Виталий Давыдов on 22.02.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
void myLsFunction(int argc, const char * argv[]) {
    const char *dirPath = NULL;
    int wasFlag = 0;
    
    if (argc == 2) {
        if (!strcmp(argv[1], "-l")) {
            dirPath = ".";
            wasFlag = 1;
        }
        else {
            dirPath = argv[1];
        }
    }
    else {
        if (argc >= 3) {
            dirPath = argv[2];
            wasFlag = 1;
        }
        else {
            dirPath = ".";
        }
    }
    
    DIR *directory = opendir(dirPath);
    if (!directory) {
        printf("%s\n", "can't find directory");
        return;
    }
    
    struct dirent *dp = NULL;
    
    while ((dp = readdir(directory)) != NULL) {
        char *name = dp->d_name;
        int len = dp->d_namlen;
        struct stat st;
        
        stat(name, &st);
        printf("%lld\t%s\n", st.st_size, name);
    }
    
    closedir(directory);     
}

int main(int argc, const char * argv[])
{
    myLsFunction(argc, argv);
    
    return 0;
}

