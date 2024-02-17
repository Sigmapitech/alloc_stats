#include <stdio.h>

#include "alloc_stats.h"

/* Linux internal program name variable. */
extern const char *__progname;

__attribute__((destructor))
void print_stats(void)
{
    size_t alloc_count = MEM_STAT.alloc + MEM_STAT.calloc;
    double calloced = 100. * ((double)MEM_STAT.calloc / (double)alloc_count);
    double freed = 100. * ((double)MEM_STAT.free / (double)alloc_count);

    fprintf(stderr,
        "\n%s:\n"
        "├─ %zu alloc (~%.2f %% calloc)\n"
        "├─ %zu freed (~%.2f %%)\n"
        "└─ %zu realloc\n",
        __progname,
        alloc_count, calloced,
        MEM_STAT.free, freed,
        MEM_STAT.realloc
    );
}
