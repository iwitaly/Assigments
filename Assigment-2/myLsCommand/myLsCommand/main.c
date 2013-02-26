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
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

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
        struct stat st;
        //пераметры, линки, владелец, группа, размер, время модификации
        char *name = dp->d_name;
        stat(name, &st);

        long long size = st.st_size;
        int hardLinks = st.st_nlink;
        int userID = st.st_uid;
        int groupID = st.st_gid;
        char *dataOfLastTimeModification = ctime(&st.st_atimespec.tv_sec);
        int fileModes = st.st_mode;
        
        printf("%lld \t %s \t %s \n", st.st_size,dataOfLastTimeModification, name);
    }
    
    closedir(directory);     
}

int main(int argc, const char * argv[])
{
    myLsFunction(argc, argv);
    
    return 0;
}

