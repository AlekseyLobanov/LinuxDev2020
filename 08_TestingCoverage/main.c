#include <stdio.h>

#include "buf.h"

int main() {
    float* values = 0;
    for (size_t i = 0; i < 25; i++)
        buf_push(values, rand() / (float)RAND_MAX);
    for (size_t i = 0; i < buf_size(values); i++)
        printf("values[%zu] = %f\n", i, values[i]);
    buf_free(values);
    return 0;
}