#ifndef MSTAT_H
    #define MSTAT_H

    #include <stdbool.h>
    #include <stddef.h>

    #define VERBOSE 1

typedef struct {
    size_t alloc;
    size_t calloc;
    size_t free;
    size_t realloc;
} mstat_t;

extern mstat_t MEM_STAT;

void resolve_symbol(void **funcp, const char *sym_name);
void print_stats(void);

/* wrapped */
void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void exit(int status);
void free(void *ptr);

#endif
