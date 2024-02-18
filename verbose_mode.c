#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alloc_stats.h"

bool VERBOSE = 0;

void lookup_env(void)
{
    static bool did_lookup = false;
    char *v = getenv("AS_VERBOSE");

    if (did_lookup)
        return;
    if (v == NULL)
        return;
    VERBOSE = !strcmp(v, "1");
    did_lookup = true;
}
