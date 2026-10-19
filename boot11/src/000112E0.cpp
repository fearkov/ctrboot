#pragma arm
#include "types.h"

// Invalidates the whole data cache.
void FUN_000112E0()
{
    register u32 invalidate __asm("cp15:0:c7:c6:0");
    invalidate = 0;
}
