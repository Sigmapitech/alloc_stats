#include <dlfcn.h>
#include <stdio.h>

#include "alloc_stats.h"

void resolve_symbol(void **funcp, const char *sym_name)
{
    lookup_env();
    if (*funcp == NULL)
        *funcp = dlsym(RTLD_NEXT, sym_name);
    if (*funcp == NULL)
        fprintf(stderr, "couldn't find symbol: [%s].", sym_name);
}
