#include <stdio.h>
#include <stdlib.h>

int main() {
    char* s = malloc(40);
    free(s);
    free(s);
    return 0;
}