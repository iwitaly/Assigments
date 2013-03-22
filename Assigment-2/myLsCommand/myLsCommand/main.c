//
//  main.c
//  myLsCommand
//
//  Created by Виталий Давыдов on 22.02.13.
//  Copyright (c) 2013 Виталий Давыдов. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>

void myLsFunction(int argc, const char * argv[]) {
    const char *dirPath = NULL;
    int wasFlag = 0;
    
    if (argc == 2) {
        if (strcmp(argv[1], "-l") == 0) {
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
        //поправить имя файла с полным путем
        //
        char *name = (char *)malloc((strlen(dp->d_name) + strlen(dirPath)+1)*sizeof(char));
        name[0] = '\0';
        name = strcat(name, dirPath);
        name = strcat(name, dp->d_name);
        
//        printf("%s\n", name);
        
        if (!wasFlag) {
            printf("%s\n", dp->d_name);
        }
        else {
            stat(name, &st);
            
            int fileModes = st.st_mode;
            long long size = st.st_size;
            int hardLinks = st.st_nlink;
            char *user = getpwuid(st.st_uid)->pw_name;
            char *group = getgrgid(st.st_gid)->gr_name;
            
            if (user == NULL || group == NULL) {
                write(STDOUT_FILENO, "error", strlen("error"));
            }
            
            //проверку на NULL
            char *dataOfLastTimeModification = ctime(&st.st_atimespec.tv_sec);
            
            char filesModes[3];
            filesModes[2] = '\0';
            
            if (fileModes | S_IRWXU) {
                filesModes[0] = 'r';
                filesModes[1] = 'w';
            }
            else {
                if (fileModes | S_IRUSR) {
                    filesModes[0] = 'r';
                }
                else {
                    if (fileModes | S_IWUSR) {
                        filesModes[0] = 'w';
                    }
                }
                    
            }
            
            printf("%s\t", filesModes);
            printf("%d\t", hardLinks);//почему так много?
            printf("%s\t", user);
            printf("%s\t", group);
            printf("%lld\t", size);
            printf("%s\t", dataOfLastTimeModification);
            printf("%s\n", name);
        }
        free(name);
    }
    
    closedir(directory);     
}

int main(int argc, const char * argv[])
{
    myLsFunction(argc, argv);
    
    return 0;
}
