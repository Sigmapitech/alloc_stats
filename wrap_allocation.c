#include <dlfcn.h>
#include <errno.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "alloc_stats.h"

mstat_t MEM_STAT = { 0 };

void *malloc(size_t size)
{
    static void *(*real)(size_t) = NULL;
    void *p;

    if (real == NULL)
        resolve_symbol((void **)&real, "malloc");

    p = real(size);
    ++MEM_STAT.alloc;
    if (VERBOSE)
        fprintf(stderr, "malloc(size=%zu) -> %p\n", size, p);
    return p;
}

void free(void *ptr)
{
    static void (*real)(void *) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "free");

    ++MEM_STAT.free;
    if (VERBOSE)
        fprintf(stderr, "free(ptr=%p)\n", ptr);
    real(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    static void *(*real)(size_t, size_t) = NULL;
    void *p;

    if (real == NULL)
        resolve_symbol((void **)&real, "calloc");

    p = real(nmemb, size);
    ++MEM_STAT.calloc;
    if (VERBOSE)
        fprintf(stderr, "calloc(nmemb=%zu, size=%zu) -> %p\n", nmemb, size, p);
    return p;
}

void *realloc(void *ptr, size_t size)
{
    static void *(*real)(void *, size_t) = NULL;
    void *p;

    if (real == NULL)
        resolve_symbol((void **)&real, "realloc");

    p = real(ptr, size);
    if (ptr == NULL)
        ++MEM_STAT.alloc;
    else
        ++MEM_STAT.realloc;
    if (VERBOSE)
        fprintf(stderr, "realloc(ptr=%p, size=%zu) -> %p\n", ptr, size, p);
    return p;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    static void *(*real)(void *, size_t, size_t) = NULL;
    void *p;

    if (real == NULL)
        resolve_symbol((void **)&real, "reallocarray");

    p = real(ptr, nmemb, size);
    if (ptr == NULL)
        ++MEM_STAT.alloc;
    else
        ++MEM_STAT.realloc;
    if (VERBOSE)
        fprintf(stderr, "realloc(ptr=%p, nmemb=%zu, size=%zu) -> %p\n",
            ptr, nmemb, size, p);
    return p;
}
