#include "types.h"

#pragma arm

// Invalidates the whole data cache.
void FUN_FFFF07F0()
{
    register u32 invalidate_dcache __asm("cp15:0:c7:c6:0");
    invalidate_dcache = 0;
}
