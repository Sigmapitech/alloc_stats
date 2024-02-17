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

    fprintf(stderr, "Call to malloc (alloc %zu)\n", ++MEM_STAT.alloc);
    return real(size);
}

void free(void *ptr)
{
    static void (*real)(void *) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "free");

    fprintf(stderr, "Call to free (%zu), [%lld remaining]\n",
        ++MEM_STAT.free, (unsigned long long)(MEM_STAT.alloc - MEM_STAT.free));
    real(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    static void *(*real)(size_t, size_t) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "calloc");

    fprintf(stderr, "Call to calloc (alloc %zu)\n", ++MEM_STAT.alloc);
    return real(nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
    static void *(*real)(void *, size_t) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "realloc");

    fprintf(stderr, "Call to realloc (%zu)\n", ++MEM_STAT.realloc);
    return real(ptr, size);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    static void *(*real)(void *, size_t, size_t) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "reallocarray");

    fprintf(stderr, "Call to reallocarray (%zu)\n", ++MEM_STAT.realloc);
    return real(ptr, nmemb, size);
}
