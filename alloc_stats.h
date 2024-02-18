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

/* From valgrind's docs:
 *
 * The GNU C library (`libc.so`), which is used by all programs, may allocate
 * memory for its own uses. Usually it doesn't bother to free that memory when
 * the program ends—there would be no point, since the Linux kernel reclaims
 * all process resources when a process exits anyway, so it would just slow
 * things down.
 *
 * The glibc authors realised that this behaviour causes leak checkers, such as
 * Valgrind, to falsely report leaks in glibc, when a leak check is done at
 * exit. In order to avoid this, they provided a routine called
 * `__libc_freeres` specifically to make glibc release all memory it has
 * allocated. Memcheck therefore tries to run `__libc_freeres` at exit.
 **/
extern void __libc_freeres(void);

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
