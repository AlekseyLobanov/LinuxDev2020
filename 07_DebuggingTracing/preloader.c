#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int (*real_unlinkat)(int dirfd, const char* pathname, int flags) = NULL;

int unlinkat(int dirfd, const char* pathname, int flags) {
    printf("unlinkat: %s\n", pathname);
    real_unlinkat = dlsym(RTLD_NEXT, "unlinkat");
    if (strstr(pathname, "FIX") != NULL)
        return EPERM;
    return real_unlinkat(dirfd, pathname, flags);
}