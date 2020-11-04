#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>

#include "minctest.h"

#include "buf.h"

void test_buf_squares_operator() {
    long* ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    lequal((int)buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    lequal(match, 10000);
    buf_free(ai);
}

void test_buf_grow_trunc() {
    long* ai = 0;
    buf_grow(ai, 1000);
    lequal((int)buf_capacity(ai), 1000);
    lequal((int)buf_size(ai), 0);
    buf_trunc(ai, 100);
    lequal((int)buf_capacity(ai), 100);
    buf_free(ai);
}

void test_buf_base() {
    float* a = 0;
    lok(buf_capacity(a) == 0);
    lok(buf_size(a) == 0);
    buf_push(a, 1.3f);
    lok(buf_size(a) == 1);
    lok(a[0] == (float)1.3f);
    buf_clear(a);
    lok(buf_size(a) == 0);
    lok(a != 0);
    buf_free(a);
    lok(a == 0);

    buf_clear(a);
    lok(buf_size(a) == 0);
    lok(a == 0);

    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    lok(buf_size(a) == 4);
    lok(buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    lok(buf_size(a) == 3);
    lok(buf_pop(a) == (float)1.3f);
    lok(buf_pop(a) == (float)1.2f);
    lok(buf_pop(a) == (float)1.1f);
    lok(buf_size(a) == 0);
    buf_free(a);
}

int main(int argc, char* argv[]) {
    lrun("buf_push(), []", test_buf_squares_operator);
    lrun("buf_grow(), buf_trunc", test_buf_grow_trunc);
    lrun("buf_base_test", test_buf_base);
    lresults();
    return lfails != 0;
}