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

void abort(void)
{
    static void (*real)(void) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "abort");

    print_stats();
    real();

    /* Ignore clangd noreturn, as we exited above */
    __builtin_unreachable();
}

void _exit(int status)
{
    static void (*real)(int) = NULL;

    if (real == NULL)
        resolve_symbol((void **)&real, "_exit");

    print_stats();
    real(status);

    /* Ignore clangd noreturn, as we exited above */
    __builtin_unreachable();
}
