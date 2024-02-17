#include "alloc_stats.h"

void exit(int status)
{
    static void (*real)(int) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "exit");

    print_stats();
    real(status);

    /* Ignore clangd noreturn, as we exited above */
    __builtin_unreachable();
}
