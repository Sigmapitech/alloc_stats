#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "alloc_stats.h"

mstat_t MEM_STAT = { 0 };

void *malloc(size_t size)
{
    static void *(*real)(size_t) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "malloc");

    ++MEM_STAT.alloc;
    return real(size);
}

void free(void *ptr)
{
    static void (*real)(void *) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "free");

    if (ptr == NULL)
        fprintf(stderr, "Called free(NULL);");
    ++MEM_STAT.free;
    real(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    static void *(*real)(size_t, size_t) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "calloc");

    ++MEM_STAT.calloc;
    return real(nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
    static void *(*real)(void *, size_t) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "realloc");

    if (ptr == NULL)
        ++MEM_STAT.alloc;
    else
        ++MEM_STAT.realloc;
    return real(ptr, size);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    static void *(*real)(void *, size_t, size_t) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "reallocarray");

    if (ptr == NULL)
        ++MEM_STAT.alloc;
    else
        ++MEM_STAT.realloc;
    return real(ptr, nmemb, size);
}
