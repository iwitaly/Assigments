#include <stdio.h>

int main(int argc, const char * argv[]) {
    while (1) {
        sleep(1);
        printf("%s\n", argv[0]);
    }
    return 0;
}