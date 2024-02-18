#include <stdio.h>

#include "alloc_stats.h"

/* Linux internal program name variable. */
extern const char *__progname;

struct computed_stat {
    size_t alloc_calls;
    double p_freed;
    double p_calloced;
};

__attribute__((destructor))
void print_stats(void)
{
    struct computed_stat cs;

    __libc_freeres();
    cs.alloc_calls = MEM_STAT.alloc + MEM_STAT.calloc;
    cs.p_calloced = 100. * ((double)MEM_STAT.calloc / (double)cs.alloc_calls);
    cs.p_freed = 100. * ((double)MEM_STAT.free / (double)cs.alloc_calls);

    fprintf(stderr,
        "\n%s:\n"
        "├─ %zu alloc (~%.2f %% calloc)\n"
        "├─ %zu freed (~%.2f %%)\n"
        "└─ %zu realloc\n",
        __progname,
        cs.alloc_calls, cs.p_calloced,
        MEM_STAT.free, cs.p_freed,
        MEM_STAT.realloc
    );
}
