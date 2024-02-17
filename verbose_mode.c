#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "alloc_stats.h"

extern char **environ;

bool VERBOSE = 0;

__attribute__((constructor))
void env_lookup(void)
{
    for (size_t i = 0; environ[i] != NULL; i++) {
        if (strcmp(environ[i], "AS_VERBOSE=1") == 0) {
            VERBOSE = 1;
            return;
        }
    }
}
