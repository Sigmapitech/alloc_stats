#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alloc_stats.h"

void __attribute__ ((constructor)) init(void)
{
    fprintf(stderr, "preload init!\n");
}

void __attribute__ ((destructor)) cleanup(void)
{
    fprintf(stderr, "preload cleanup!\n");
}
