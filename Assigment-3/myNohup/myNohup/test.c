#include <stdio.h>

int main(int argc, const char * argv[]) {
    FILE *file = fopen("/Users/iwitaly/Documents/Assigments/Assigment-3/myNohup/myNohup/text.txt", "a");
    while (1) {
        fprintf(file, "1\n");
    }

    return 0;
}